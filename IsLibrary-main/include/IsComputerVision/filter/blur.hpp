#pragma once

#include <IsComputerVision/common.hpp>

/**
 * @todo
 * [OK] Avarage Filter
 * [OK] Gaussian Filter
 * [OK] Median Filter
 * [OK] Mosic Filter
 * [] Birateral Filter
 * [] Gabol Filter
 * @note
 * [] Variance Filter
 * [] MaxMin Filter
 */

namespace is
{
    namespace imgproc
    {
        using namespace nbla;

        /**
         * @brief 平均値フィルタ
         * 
         * @param src 
         * @param ksize_x 
         * @param ksize_y 
         * @return NdArrayPtr
         */
        IS_IMGPROC_API NdArrayPtr avg_filter(NdArrayPtr src, const Size &ksize);

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
        IS_IMGPROC_API NdArrayPtr gaussian_filter(NdArrayPtr src, int ksize, double sigma = 0);

        /**
         * @brief メディアンフィルタ
         * 
         * @param src 
         * @param ksize_x 
         * @param ksize_y 
         * @return NdArrayPtr 
         */
        IS_IMGPROC_API NdArrayPtr median_filter(NdArrayPtr src, int ksize);


        /**
         * @brief モザイクフィルタ
         * 
         * @param src 
         * @param block 
         * @return NdArrayPtr
         */
        IS_IMGPROC_API NdArrayPtr mozic_filter(NdArrayPtr src, int block);
    }
}