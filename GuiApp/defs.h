/**
 * @file defs.h
 * @author your name (you@domain.com)
 * @brief GuiAppプロジェクトの各種定義ファイル
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <cassert>

#include <string>
using namespace std::literals::string_literals;




typedef struct ZoomLebel
{
    int index{0};
    float levels[23] = {1.f / 72, 1.f / 48, 1.f / 32, 1.f / 24, 1.f / 16, 1.f / 12, 1.f / 8, 1.f / 6, 1.f / 4, 1.f / 3, 1.f / 2,
                        0.75f, 1.0f, 1.5f, 2.0f, 3.0f, 4.0f, 6.0f, 8.0f, 12.0f, 16.0f, 24.0f, 32.0f};

    float operator[](int i)
    {
        assert(i >= 0);
        int length = sizeof(levels) / sizeof(float);
        assert(i < length);
        return levels[i];
    }
} ZoomLevel;




// /**
//  * ImageDrawScene上で扱うオブジェクトタイプ
//  * */
// enum class VisualObjectType : int
// {
//     ROI = 0,
//     LINE,
//     ELLIPSE,
//     CROSS_LINE,
//     PROFILE_X,
//     PROFILE_Y,
//     MASK,
// };


