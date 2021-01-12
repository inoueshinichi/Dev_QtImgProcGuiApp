#ifndef __COMMON_H__
#define __COMMON_H__

// 自作
#include "defs.hpp"

// Standard
#include <cstdio>  // std::snprintf()
#include <cstdlib> // std::abort()
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Qt

using std::string;
using std::vector;
using std::snprintf;
using std::ostringstream;


// string formatter
template <typename T, typename... Args>
string format_string(const string& format, T first, Args... rest)
{
    // 文字列サイズを取得
    int size = snprintf(nullptr, 0, format.c_str(), first, rest...);

    if (size < 0)
    {
        std::printf("fatal error in format_string function snprintf() failed\n");
        std::abort();
    }
    vector<char> buf(size + 1); // 文字列＋ヌル文字
    snprintf(buf.data(), size + 1, format.c_str(), first, rest...);

    return string(buf.data(), buf.data() + size);
}
#endif