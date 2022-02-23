/**
 * @file gaussian_filter.hpp
 * @author your name (you@domain.com)
 * @brief ガウシアンフィルタ
 * @version 0.1
 * @date 2022-02-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <IsComputerVision/IsComputerVision.hpp>

namespace is
{
    namespace imgproc
    {
        using namespace nbla;

        /**
         * @brief ガウシアンフィルタ
         *
         * @param src
         * @param ksize_x
         * @param ksize_y
         * @param sigma_x
         * @param sigma_y
         * @return NdArrayPtr
         */
        IS_IMGPROC_API NdArrayPtr gaussian(NdArrayPtr src, int ksize, double sigma = 0);
    }
}