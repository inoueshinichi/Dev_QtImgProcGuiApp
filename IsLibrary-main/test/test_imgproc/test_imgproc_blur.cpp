#include <gtest/gtest.h>

// #include "matplotlibcpp.h"
// namespace plt = matplotlibcpp;

#include <IsCommon/tm.hpp>

// nbla
#include <IsNdArray/nd_array_extra.hpp>

// imgproc
#include <IsComputerVision/common.hpp>
#include <IsComputerVision/io/img_io.hpp>

// filter
#include <IsComputerVision/filter/utils/utils_filter.hpp>
#include <IsComputerVision/filter/blur.hpp>
#include <IsComputerVision/filter/edge_detector.hpp>

// utility
#include <test_utils.hpp>

#include <string>
#include <cstdio>

using uchar = unsigned char;
using namespace is::nbla;
using namespace is::common;
using namespace is::imgproc;

#define PADDING_ZERO 0
#define PADDING_MEAN 1
#define PADDING_REFLECT 2
#define PADDING_REPLICATE 3
#define PADDING_WARP 4

namespace {

    // Padding
    TEST(imgproc_func, padding) {
        const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
        // std::string dummy_filename = "/home/inoue/Images/Mono/256X256/Tree.bmp";
        std::string dummy_filename = "/home/inoue/Images/Color/Lenna.bmp";

        // io
        ImageIo<format::BmpFile> io_bmp;
        auto src = io_bmp.load(dummy_filename, false);

        // src
        auto in_shape = src->shape();
        auto in_strides = src->strides();
        show_ndarray_property(src);

        // padding
        int pad_x = 5;
        int pad_y = 5;
        auto pad = padding<uchar>(src, pad_x, pad_x, PADDING_REPLICATE);
        show_ndarray_property(pad);

        dummy_filename = format_string("/home/inoue/Desktop/paddingLenna_%dx%d.bmp", 
                                        pad_x, pad_y);
        io_bmp.save(dummy_filename, pad, false);
    }

    // SaturateCast
    TEST(imgproc_func, saturate_cast) {
        const auto &ctx =
          SingletonManager::get<GlobalContext>()->get_current_context();
      
        using ubyte = unsigned char;
        auto ndarray = zeros<float>(Shape_t{3, 3, 3});
        show_ndarray_property(ndarray);
        show_ndarray_contents<float>(ndarray);
        auto sh = ndarray->shape();
        auto st = ndarray->strides();

        float *data = ndarray->cast_data_and_get_pointer<float>(ctx);
        data[0 * st[0] + 0 * st[1] + 0 * st[2]] = -1;
        data[0 * st[0] + 1 * st[1] + 1 * st[2]] = 255;
        data[0 * st[0] + 2 * st[1] + 2 * st[2]] = 256;
        data[1 * st[0] + 0 * st[1] + 0 * st[2]] = 257;
        data[1 * st[0] + 1 * st[1] + 1 * st[2]] = 127;
        data[1 * st[0] + 2 * st[1] + 2 * st[2]] = 128;


        std::cout << "non zero" << std::endl;

        show_ndarray_contents<float>(ndarray);

        // std::cout << "add_scalar: 128" << std::endl;
        // ndarray = add_scalar<float>(ndarray, 128); // nd_array_extra.hppでエラー発生中
        // show_ndarray_contents<float>(ndarray);

        // 正しい動作確認済み
        // std::cout << "saturate clamp: float -> byte" << std::endl;
        // ndarray = saturate_clamp<char>(ndarray);
        // show_ndarray_contents<float>(ndarray);

        // 正しい動作確認済み
        // std::cout << "cast_data_and_get_pointer: float -> byte" << std::endl;
        // ndarray->cast(dtypes::BYTE, ctx);
        // show_ndarray_contents<float>(ndarray);
    }

    // AverageFilter
    TEST(imgproc_func, avg_filter)
    {
        const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
        std::cout << "GlobalContext after load: " << ctx.to_string() << std::endl;

        // std::string dummy_filename = "/home/inoue/Images/Mono/256X256/Tree.bmp";
        std::string dummy_filename = "/home/inoue/Images/Color/Lenna.bmp";

        // io
        ImageIo<format::BmpFile> io_bmp;
        auto src = io_bmp.load(dummy_filename, false);

        // src
        auto in_shape = src->shape();
        auto in_strides = src->strides();
        // show_ndarray_property(src);

        int ksize_x = 15;
        int ksize_y = 15;
        auto filtered = invoke_tm_chrono_ms_ret(avg_filter, src, Size(ksize_x, ksize_y));
        // show_ndarray_property(filtered);

        dummy_filename = format_string("/home/inoue/Desktop/average_Lenna_%dx%d.bmp", 
                                        ksize_x, ksize_y);
        io_bmp.save(dummy_filename, filtered, false);
    }

    // GaussianFilter
    TEST(imgproc_func, gaussian_filter)
    {
        const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
        std::cout << "GlobalContext after load: " << ctx.to_string() << std::endl;

        // std::string dummy_filename = "/home/inoue/Images/Mono/256X256/Tree.bmp";
        std::string dummy_filename = "/home/inoue/Images/Color/Lenna.bmp";

        // io
        ImageIo<format::BmpFile> io_bmp;
        auto src = io_bmp.load(dummy_filename, false);

        // src
        auto in_shape = src->shape();
        auto in_strides = src->strides();
        // show_ndarray_property(src);

        int ksize = 9;
        auto filtered = invoke_tm_chrono_ms_ret(gaussian_filter, src, ksize, 0);
        // show_ndarray_property(filtered);

        dummy_filename = format_string("/home/inoue/Desktop/gaussian_Lenna_size%dx%d.bmp",
                                        ksize, ksize);
        io_bmp.save(dummy_filename, filtered, false);
    }

    // MedianFilter
    TEST(imgproc_func, median_filter)
    {
        const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
        std::cout << "GlobalContext after load: " << ctx.to_string() << std::endl;

        // std::string dummy_filename = "/home/inoue/Images/Mono/256X256/Tree.bmp";
        std::string dummy_filename = "/home/inoue/Images/Color/Lenna.bmp";

        // io
        ImageIo<format::BmpFile> io_bmp;
        auto src = io_bmp.load(dummy_filename, false);

        // src
        auto in_shape = src->shape();
        auto in_strides = src->strides();
        // show_ndarray_property(src);

        int ksize = 9;
        auto filtered = invoke_tm_chrono_ms_ret(median_filter, src, ksize);
        // show_ndarray_property(filtered);

        dummy_filename = format_string("/home/inoue/Desktop/median_Lenna_%dx%d.bmp", 
                                        ksize, ksize);
        io_bmp.save(dummy_filename, filtered, false);
    }
}       

int main(int, char**)
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}