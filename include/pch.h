#ifndef __IS_PCH_H__
#define __IS_PCH_H__

#include <cstddef>
#include <limits>
#include <climits>
#include <cfloat>
#include <cstdint>
#include <cstdlib>
#include <new>
#include <typeinfo>
#include <exception>
#include <initializer_list>
#include <cstdalign>
#include <stdexcept>
#include <cassert>
#include <cerrno>
#include <system_error>

#if __has_include(<string_view>)
#   include <string_view>
#endif

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iterator>
#include <algorithm>
#include <cfenv>
#include <random>
#include <numeric>
#include <cmath>
#include <iosfwd>
#include <ios>
#include <streambuf>
#include <istream>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <iostream>

#if __has_include(<filesystem>)
#	include <filesystem>
#endif

#include <cstdio>
#include <cinttypes>

#include <regex>
#include <atomic>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <future>

#include <chrono>
#include <ctime>

#include <locale>      // std::wstring_convert
#include <codecvt>     // std::codecvt_utf8
#include <bitset>      
#include <type_traits>

  
using namespace std::literals;

#if defined(WIN32)

// C Runtime Library
#include <io.h>        // _isatty()

// Windows
#include <Windows.h>
#include <WinUser.h>
// #include <CommCtrl.h>  // コモンコントロール(Tool Bar & Status Bar etc..)
#include <atlstr.h>    // CString
#endif()

namespace Is
{
    /**
     * 現在の日時を取得
     * */
    std::string return_current_datetime();

}


#endif // __PCH_HPP__