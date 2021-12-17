/**
 * @file test_nnabla_func_asin.cpp
 * @author your name (you@domain.com)
 * @brief [Test] Nnabla asin-func
 * @version 0.1
 * @date 2021-12-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
// googletest
#include <gtest/gtest.h>

// nnabla
#include <test_nnabla.hpp>

// test utils
#include <test_utils.hpp>

namespace 
{
    TEST(nnabla_func, asin_1)
    {
        using namespace std;
        const auto& ctx_cpu = SingletonManager::get<GlobalContext>()->get_current_context();

        // zero
        auto ndarray_zeros = zeros<float>(Shape_t{12, 12});
        auto st = ndarray_zeros->strides();
        auto sh = ndarray_zeros->shape();
        float* data = ndarray_zeros->cast_data_and_get_pointer<float>(ctx_cpu);

        data[0 * st[0] + 0 * st[1]] = 1.0 / sqrt(2);
        data[1 * st[0] + 1 * st[1]] = sqrt(3) / 2.0;
        data[2 * st[0] + 2 * st[1]] = 1.0;

        show_ndarray_contents<float>(ndarray_zeros);

        cout << "---" <<endl;

        auto out_ndarray = is::common::invoke_tm_chrono_ms_ret(asin<float>, ndarray_zeros);

        show_ndarray_contents<float>(out_ndarray);
    }


    TEST(nnabla_func, asin_2)
    {
        using namespace std;
        const auto& ctx_cpu = SingletonManager::get<GlobalContext>()->get_current_context();

        // zero
        auto ndarray_zeros = zeros<float>(Shape_t{12, 12});
        auto st = ndarray_zeros->strides();
        auto sh = ndarray_zeros->shape();
        float* data = ndarray_zeros->cast_data_and_get_pointer<float>(ctx_cpu);

        data[0 * st[0] + 0 * st[1]] = 1.0 / sqrt(2);
        data[1 * st[0] + 1 * st[1]] = sqrt(3) / 2.0;
        data[2 * st[0] + 2 * st[1]] = 1.0;

        show_ndarray_contents<float>(ndarray_zeros);

        cout << "---" <<endl;

        for (int y = 0; y < sh[0]]; ++y)
        {
            for (int x = 0; x < sh[1]; ++x)
            {
                auto& v = data[y * st[0] + x * st[1]];
                v = asin(v);
            }
        }
    
        show_ndarray_contents<float>(ndarray_zeros);
    }
}

int main(int, char**)
{
    std::cout << __FILE__ << std::endl;
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

