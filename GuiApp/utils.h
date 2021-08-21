#pragma once

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
    std::string format_string_internal(const std::string &format, Args &&...args)
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
std::string format_string(const std::string &format, Args &&...args)
{
    /* 各パラメータの型を変換して、文字列のフォーマッティング */
    return detail::format_string_internal(format, detail::convert(std::forward<Args>(args))...);
}




inline std::string getNewSerialNoFilename(const std::string &filename,
                                          const std::set<std::string> &filenameSet) {
    /* 最新の連番付きファイル名を取得する.
       連番の付け方: name(-番号).拡張子
       ※番号の最大値+1を新たな番号とするので, 途中歯抜けになっている番号は無視する.
    */
    std::string pattern = R"(^.+\..+$)"; // 拡張子の有無
    std::regex re0(pattern);
    std::smatch match;
    if (std::regex_match(filename, match, re0)) {
        // 拡張子付きの場合

        if (!filenameSet.contains(filename)) {
            return filename;
        }

        std::string name;
        std::string ext;
        pattern = R"(^(.+)-([0-9]+)\.(.+)$)";
        std::regex re1(pattern);
        int no = -1;
        if (std::regex_match(filename, match, re1)) {
            // 連番付き
            name = match[1];
            no = std::stoi(match[2]);
            ext = match[3];
        }
        else {
            auto pos = filename.rfind('.');
            if (pos != std::string::npos) {
                name = filename.substr(0, pos); // Head
                ext = filename.substr(pos + 1); // Tail
            }
            else {
                return std::string();
            }
        }

        // filenameSetにあるファイル名を検索
        pattern = format_string(R"(^(%s-[0-9]+|(%s-%d-[0-9]+))\.(%s)$)", name.c_str(), name.c_str(), no, ext.c_str());
        std::regex re2(pattern);
        int count = 0;
        int subCount = 0;
        bool isDoubleCount = false;
        for (auto iter = filenameSet.begin(); iter != filenameSet.end(); ++iter) {
            if (std::regex_match(*iter, match, re2)) {
                count++;
                if (filename == match[0])
                    isDoubleCount = true;
                std::string nameWithIndex = match[2];
                if (!nameWithIndex.empty()) {
                    subCount++;
                }
            }
        }

        std::string newFilename;
        if (isDoubleCount) {
            newFilename = format_string("%s-%d-%d.%s", name.c_str(), no, subCount, ext.c_str());
        }
        else {
            newFilename = format_string("%s-%d.%s", name.c_str(), count - subCount, ext.c_str());
        }

        return newFilename;
    }
    else {
        return std::string();
    }
}