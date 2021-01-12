#ifndef __DEFS_H__
#define __DEFS_H__

// 自作

// Standard
#include <string>

// Qt


using namespace std::literals::string_literals;

/**
 * ImageDrawScene上で扱うオブジェクトタイプ
 * */
enum class VisualObjectType : int
{
    ROI = 0,
    LINE,
    ELLIPSE,
    CROSS_LINE,
    PROFILE_X,
    PROFILE_Y,
    MASK,
};
#endif