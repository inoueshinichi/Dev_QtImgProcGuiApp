/**
 * @file utility.h
 * @author inoue shinichi (inoue.shinichi.1800@gmail.com)
 * @brief GuiAppプロジェクトにおける自作関数用Headerファイル
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "common.h"

#include <set>
#include <regex>
#include <memory>
#include <vector>
#include <string>
#include <cstdio>  // std::snprintf
#include <cstdlib> // std::abort
#include <iostream>
#include <sstream>

namespace detail
{

#if __cplusplus >= 201703L
    // C++17以上

    /* std::string型をconst char*に変換し、それ以外はそのまま出力 */
    template <typename T>
    auto convert(T &&value)
    {
        /* std::string型をconst char*に変換 */
        if constexpr (std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, std::string>::value)
        {
            return std::forward<T>(value).c_str();
        }
        /* std::string型以外は、そのまま出力 */
        else
        {
            return std::forward<T>(value);
        }
    }
#else
    // C++11, 14

    /* std::string型をconst char*に変換 */
    template <typename T, typename std::enable_if_t<std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, std::string>::value>::type * = nullptr>
    auto convert(T &&value)
    {
        return std::forward<T>(value).c_str();
    }

    /* std::string型以外は、そのまま出力 */
    template <typename T, typename std::enable_if_t<!std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, std::string>::value>::type * = nullptr>
    auto convert(T &&value)
    {
        return std::forward<T>(value);
    }
#endif

    /* 文字列のフォーマッティング(内部処理) */
    template <typename... Args>
    std::string formatStringInternal(const std::string &format, Args &&...args)
    {
        /* フォーマット後の文字数を算出 */
        int size = std::snprintf(nullptr, 0, format.c_str(), std::forward<Args>(args)...);
        if (size < 0)
        {
            std::printf("Fatal error: std::snprintf() in is::detail::format_string_internal().\n");
            std::abort();
        }

        /* バッファサイズを算出(文字列長 + null文字サイズ) */
        size_t buf_size = size + sizeof(char);

        /* バッファサイズ分メモリ確保 */
        std::vector<char> buf(buf_size);

        /* 文字列のフォーマット */
        std::snprintf(buf.data(), buf_size, format.c_str(), std::forward<Args>(args)...);

        /* 文字列をstd::string型に変換して出力 */
        return std::string(buf.data(), buf.data() + size);
    }
} // detail

/* 文字列のフォーマッティング */
template <typename... Args>
std::string formatString(const std::string &format, Args &&...args)
{
    /* 各パラメータの型を変換して、文字列のフォーマッティング */
    return detail::formatStringInternal(format, detail::convert(std::forward<Args>(args))...);
}

///////////////////////////////////////////////////////////////////////////////////////
// Global関数
///////////////////////////////////////////////////////////////////////////////////////

std::string getNewSerialNoFilename(const std::string &filename,
                                    const std::set<std::string> &filenameSet); 