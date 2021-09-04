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

#if 1
#include <cstdio>
#define DEBUG_STREAM(format, ...) std::printf(format, ##__VA_ARGS__)
#else
#define DEBUG_STREAM(format, ...)
#endif

#include "defs.h"
#include "qt_defs.h"

