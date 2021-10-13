#pragma once

#include <IsComputerVision/common.hpp>

/**
 * @todo
 * ○ Sobel
 * ○ Laplacian
 * Laplacian Of Gaussian(LOG)
 * DOG
 * Canny
 */

namespace is
{
    namespace imgproc
    {
        using namespace nbla;

        /**
         * @brief Sobel
         * 
         * @param src 
         * @param direction 
         * @return NdArrayPtr 
         */
        IS_IMGPROC_API NdArrayPtr sobelFilter(NdArrayPtr src, int direction);

        /**
         * @brief Laplacian
         *
         * @param src
         * @param is_elem_8
         * @return NdArrayPtr
         */
        IS_IMGPROC_API NdArrayPtr laplacianFilter(NdArrayPtr src, bool is_elem_8 = true);

        /**
         * @brief LoG (Laplacian of Gaussian)
         * ノイズ除去 + 輪郭線抽出
         * @param src
         * @param sigma
         * @return NdArrayPtr
         */
        IS_IMGPROC_API NdArrayPtr logFilter(NdArrayPtr src, double sigma = 0);

    } // imgproc
}