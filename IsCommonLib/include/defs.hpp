/**
 * @file defs.hpp
 * @author your name (you@domain.com)
 * @brief ライブラリ用定義
 * @version 0.1
 * @date 2021-08-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#if defined(_MSC_VER)
// __func__の定義
#define __func__ __FUNCTION__
#endif

// dll/lib
#if defined(_MSC_VER) && !defined(__CUDACC__)
    #if defined(IsCommonLib_EXPORTS) || defined(IsCommonLib_dbg_EXPORTS)
        #define IS_COMMONLIB_API __declspec(dllexport)
    #else
        #define IS_COMMONLIB_API __declspec(dllimport)
    #endif
#else
    #define IS_COMMONLIB_API
#endif

// debug log
#if 1
#include <cstdio>
#define DEBUG_STREAM(FORMAT, ...) std::printf(FORMAT, ##__VA_ARGS__)
#else
#define DEBUG_STREAM(FORMAT, ...)
#endif

// コピーコンストラクタとコピー代入演算子の外部公開を禁止する
#define DISABLE_COPY_AND_ASSIGN(CLASS_NAME)    \
private:                                       \
    CLASS_NAME(const CLASS_NAME &);            \
    CLASS_NAME &operator=(const CLASS_NAME &);