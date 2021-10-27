#include <IsComputerVision/filter/utils/utils_filter.hpp>
#include <IsComputerVision/filter/blur.hpp>


namespace is
{
    namespace imgproc
    {
        using uchar = unsigned char;


        NdArrayPtr avg_filter(NdArrayPtr src, const Size& ksize)
        {
            IS_CHECK_NDARRAY_SHAPE_AS_IMAGE(src);
            IS_DEBUG_CHECK_NDARRAY_STATE(avg_filter, IS_DEBUG_FLAG, src);

            const auto& ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            auto sh = src->shape();
            auto st = src->strides();

            int ksize_x = ksize.width();
            int ksize_y = ksize.height();
            if (ksize_x % 2 == 0)
                ksize_x += 1;
            if (ksize_y % 2 == 0)
                ksize_y += 1;

            int hlf_ksx = (int)(ksize_x / 2);
            int hlf_ksy = (int)(ksize_y / 2);

            // 平均値カーネル
            int kernel_size = ksize_x * ksize_y;
            double *p_kernel = new double[kernel_size];
            IS_ZERO_MEMORY(p_kernel, sizeof(double) * kernel_size);
            for (int k = 0; k < kernel_size; ++k)
                p_kernel[k] = 1.0 / kernel_size;

            // パディング
            auto extend = padding<uchar>(src, hlf_ksx, hlf_ksy, IS_PADDING_MEAN);
            
            // 演算結果
            auto dst = zeros<uchar>(sh);

            auto start = std::chrono::high_resolution_clock::now();

            // 畳み込み演算
            convolution<uchar>(dst, extend, Size(ksize_x, ksize_y), p_kernel);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Convolution: " << duration << "[ms]" << std::endl;

            delete[] p_kernel;

            return dst;
        }


        NdArrayPtr gaussian_filter(NdArrayPtr src, int ksize, double sigma)
        {
            IS_CHECK_NDARRAY_SHAPE_AS_IMAGE(src);
            IS_DEBUG_CHECK_NDARRAY_STATE(gaussian_filter, IS_DEBUG_FLAG, src);
            using ubyte = uchar;

            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            auto sh = src->shape();
            auto st = src->strides();

            if (ksize % 2 == 0)
                ksize += 1;

            int hlf_ks = (int)(ksize / 2);

            // ガウシアンカーネル(2次の正規分布)

            // http://opencv.jp/opencv-2.1/cpp/image_filtering.html#getGaussianKernel
            sigma = (sigma != 0) ? sigma : 0.3 * (ksize / 2 - 1) + 0.8;
            IS_DEBUG_STREAM("sigma: %.3f\n", sigma);

            int kernel_size = ksize * ksize;
            double *p_kernel = new double[kernel_size];
            int dx, dy;
            double e, val;
            double sum = 0;

            sum = 0;
            for (int j = 0; j < ksize; ++j) {
              for (int i = 0; i < ksize; ++i) {
                dy = j - hlf_ks;
                dx = i - hlf_ks;
                e = -1 * (dy * dy + dx * dx) / (2 * sigma * sigma);
                val = std::exp(e);
                p_kernel[j * ksize + i] = val;
                sum += val;
              }
            }
            for (int k = 0; k < kernel_size; ++k) {
                p_kernel[k] /= sum;
            }

            // パディング
            auto extend = padding<ubyte>(src, hlf_ks, hlf_ks, IS_PADDING_MEAN);

            // 演算結果
            auto dst = zeros<ubyte>(sh);

            auto start = std::chrono::high_resolution_clock::now();

            // 畳み込み演算
            convolution<ubyte>(dst, extend, Size(ksize, ksize), p_kernel);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Convolution: " << duration << "[ms]" << std::endl;
            delete[] p_kernel; p_kernel = nullptr;
            return dst;
        }


        NdArrayPtr median_filter(NdArrayPtr src, int ksize)
        {
            IS_CHECK_NDARRAY_SHAPE_AS_IMAGE(src);
            IS_DEBUG_CHECK_NDARRAY_STATE(median_filter, IS_DEBUG_FLAG, src);
            using ubyte = uchar;

            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            auto sh = src->shape();
            auto st = src->strides();
            int channels = sh.at(0);
            int height = sh.at(1);
            int width = sh.at(2);

            if (ksize % 2 == 0)
                ksize += 1;

            int hlf_ks = (int)(ksize / 2);

            // パディング
            auto extend = padding<ubyte>(src, hlf_ks, hlf_ks, IS_PADDING_MEAN);
            auto exsh = extend->shape();
            auto exst = extend->strides();
            ubyte *ex_data = extend->cast_data_and_get_pointer<ubyte>(ctx);


            // 演算結果
            auto dst = zeros<ubyte>(sh);
            ubyte *dst_data = dst->cast_data_and_get_pointer<ubyte>(ctx);

            /*チャネル毎のヒストグラム*/
            // 256, 128, 64, 32, 16, 8, 4, 2, (1) 
            const int HIST_NUM = 8;
            int **pp_hists = new int*[HIST_NUM];
            int *p_bins = new int[HIST_NUM];
            for (int k = 0, range = 256; k < HIST_NUM; ++k, range /= 2) {
                pp_hists[k] = new int[range];
                IS_ZERO_MEMORY(pp_hists[k], sizeof(int) * range);
                p_bins[k] = 256 / range;
            }
    

            /*ヒストグラムを用いて中央値を求める*/
            // https://qiita.com/YVT/items/7734b342894c2f8247b3

            int mid = (ksize * ksize / 2) + 1; // 1スタート 3x3=9個なら1,2,3,4,5,6,7,8,9の5番
            for (int c = 0; c < channels; ++c) {
              for (int y = 0, ex_y = hlf_ks; y < height; ++y, ++ex_y) {
                for (int x = 0, ex_x = hlf_ks; x < width; ++x, ++ex_x) {
                    
                    if (x == 0) {
                        
                        // ヒストグラム初期化
                        for (int k = 0, range = 256; k < HIST_NUM; ++k, range /= 2) {
                            IS_ZERO_MEMORY(pp_hists[k], sizeof(int) * range);
                        }

                        // 階層bin別のヒストグラムを求める
                        for (int j = 0; j < ksize; ++j) {
                            for (int i = 0; i < ksize; ++i) {
                                const auto& lum = ex_data[c * exst[0] + (y + j) * exst[1] + i * exst[2]];
                                for (int k = 0; k < HIST_NUM; ++k) {
                                    pp_hists[k][lum / p_bins[k]] += 1;
                                }
                            }
                        }

                    }
                    else {
                        // 減らす
                        int l = x - 1;
                        for (int j = 0; j < ksize; ++j) {
                            const auto& lum = ex_data[c * exst[0] + (y + j) * exst[1] + l * exst[2]];

                            // 各階層のhist
                            for (int k = 0; k < HIST_NUM; ++k) {
                                int index = lum / p_bins[k];
                                pp_hists[k][index] -= 1;
                            }
                        }
                        // 増やす
                        int r = l + ksize;
                        for (int j = 0; j < ksize; ++j) {
                            const auto& lum = ex_data[c * exst[0] + (y + j) * exst[1] + r * exst[2]];

                            // 各階層のhist
                            for (int k = 0; k < HIST_NUM; ++k) {
                                int index = lum / p_bins[k];
                                pp_hists[k][index] += 1;
                            }
                        }
                    }

                    
                    // binの大きなヒストグラムから辿ってメディアンな輝度を求める.
                    ubyte index; // median lum
                    ubyte first, last, sum_hist;
                    int hierarchy_idx = HIST_NUM - 1;
                    first = 0; last = 256 / p_bins[hierarchy_idx];
                    sum_hist = 0; // 累積ヒストグラム
                    while (hierarchy_idx >= 0) {
                        for (index = first; index < last; ++index) {
                            int judge_sum_hist = sum_hist + pp_hists[hierarchy_idx][index];
                            if (mid <= judge_sum_hist) {
                                first = 2 * index;
                                last = 2 * (index + 1);
                                break;
                            }
                            else {
                                sum_hist += pp_hists[hierarchy_idx][index];
                            }
                            
                        }
                        hierarchy_idx--;
                    }
                    
                    dst_data[c * st[0] + y * st[1] + x * st[2]] = index;
                    
                }
              }
            }

            // メモリ破棄
            delete[] p_bins; p_bins = nullptr;
            for (int i = 0; i < HIST_NUM; ++i) {
                delete[] pp_hists[i]; pp_hists[i] = nullptr;
            }
            delete[] pp_hists; pp_hists = nullptr;

            return dst;
        }
    } // imgproc
}