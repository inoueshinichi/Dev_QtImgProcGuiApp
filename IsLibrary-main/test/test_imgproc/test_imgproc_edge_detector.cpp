#include <gtest/gtest.h>

#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

#include <utils/time_measure.hpp>

// imgproc
#include <imgproc/common.hpp>
#include <imgproc/io/img_io.hpp>

// filter
#include <imgproc/filter/utils/utils_filter.hpp>
#include <imgproc/filter/blur.hpp>
#include <imgproc/filter/edge_detector.hpp>

// utility
#include <test_utils.hpp>

#include <string>
#include <cstdio>

using uchar = unsigned char;
using namespace is::nbla;
using namespace is::utils;
using namespace is::imgproc;

namespace
{
    TEST(imgproc_func, sobel) {
        const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
        std::cout << "GlobalContext after load: " << ctx.to_string() << std::endl;

        // std::string dummy_filename = "/home/inoue/Images/Mono/256X256/Tree.bmp";
        std::string dummy_filename = "/home/inoue/Images/Mono/512X512/barbara512.bmp";

        // io
        ImageIo<format::BmpFile> io_bmp;
        auto src = io_bmp.load(dummy_filename, false);

        // src
        auto sh = src->shape();
        auto st = src->strides();
        // show_ndarray_property(src);

        int direction = 0;
        auto filtered = invoke_tm_chrono_ms_ret(sobelFilter, src, direction);
        double *dst_data = filtered->cast_data_and_get_pointer<double>(ctx);

        // 基準輝度を128にする
        for (int c = 0; c < sh[0]; ++c)
        {
            for (int j = 0; j < sh[1]; ++j)
            {
                for (int i = 0; i < sh[2]; ++i)
                {
                    double v = dst_data[st[0] * c + st[1] * j + st[2] * i];
                    v += 128;
                    dst_data[st[0] * c + st[1] * j + st[2] * i] =
                        saturate_cast<uchar>(v); // Clamp
                }
            }
        }

        // double -> uchar
        filtered->cast_data_and_get_pointer<uchar>(ctx);

        // show_ndarray_property(filtered);

        dummy_filename = format_string("/home/inoue/Desktop/sobel_barbara512_dir%d.bmp",
                                       direction);
        io_bmp.save(dummy_filename, filtered, false);
    }

    TEST(imgproc_func, laplacian) {
      const auto &ctx =
          SingletonManager::get<GlobalContext>()->get_current_context();
      std::cout << "GlobalContext after load: " << ctx.to_string() << std::endl;

      // std::string dummy_filename =
      // "/home/inoue/Images/Mono/256X256/Tree.bmp";
      std::string dummy_filename =
          "/home/inoue/Images/Mono/512X512/barbara512.bmp";

      // io
      ImageIo<format::BmpFile> io_bmp;
      auto src = io_bmp.load(dummy_filename, false);

      // src
      auto sh = src->shape();
      auto st = src->strides();
      // show_ndarray_property(src);

      int direction = 0;
      auto filtered = invoke_tm_chrono_ms_ret(laplacianFilter, src, true);
      double *dst_data = filtered->cast_data_and_get_pointer<double>(ctx);

      // 基準輝度を128にする
      for (int c = 0; c < sh[0]; ++c) {
        for (int j = 0; j < sh[1]; ++j) {
          for (int i = 0; i < sh[2]; ++i) {
            double v = dst_data[st[0] * c + st[1] * j + st[2] * i];
            v += 128;
            dst_data[st[0] * c + st[1] * j + st[2] * i] =
                saturate_cast<uchar>(v);  // Clamp
          }
        }
      }

      // double -> uchar
      filtered->cast_data_and_get_pointer<uchar>(ctx);

      // show_ndarray_property(filtered);

      dummy_filename = format_string(
          "/home/inoue/Desktop/laplacian_barbara512_dir%d.bmp", direction);
      io_bmp.save(dummy_filename, filtered, false);
    }

    TEST(imgproc_func, log) {
        const auto &ctx =
            SingletonManager::get<GlobalContext>()->get_current_context();
        std::cout << "GlobalContext after load: " << ctx.to_string() << std::endl;

        // std::string dummy_filename =
        // "/home/inoue/Images/Mono/256X256/Tree.bmp";
        std::string dummy_filename =
            "/home/inoue/Images/Mono/512X512/barbara512.bmp";

        // io
        ImageIo<format::BmpFile> io_bmp;
        auto src = io_bmp.load(dummy_filename, false);

        // src
        auto sh = src->shape();
        auto st = src->strides();
        // show_ndarray_property(src);

        auto filtered = invoke_tm_chrono_ms_ret(logFilter, src, 0);
        double *dst_data = filtered->cast_data_and_get_pointer<double>(ctx);

        // 基準輝度を128にする
        for (int c = 0; c < sh[0]; ++c) {
            for (int j = 0; j < sh[1]; ++j) {
            for (int i = 0; i < sh[2]; ++i) {
                double v = dst_data[st[0] * c + st[1] * j + st[2] * i];
                v += 128;
                dst_data[st[0] * c + st[1] * j + st[2] * i] =
                    saturate_cast<uchar>(v);  // Clamp
            }
            }
        }

        // double -> uchar
        filtered->cast_data_and_get_pointer<uchar>(ctx);

        // show_ndarray_property(filtered);

        dummy_filename = format_string(
            "/home/inoue/Desktop/log_barbara512.bmp");
        io_bmp.save(dummy_filename, filtered, false);
    }
}

int main(int, char **)
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}