/**
 * @file common.h
 * @author inoue shinichi (inoue.shinichi.1800@gmail.com)
 * @brief GuiAppプロジェクトの共通Headerファイル
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "defs.h"
#include "qt_defs.h"

#if 1
#   include <cstdio>
#   define DEBUG_STREAM(FORMAT, ...) std::printf(FORMAT, ##__VA_ARGS__)
#else
#   define DEBUG_STREAM(FORMAT, ...) 
#endif