#include "pch.h"

namespace Is
{
    /**
     * 現在の日時を取得
     * */
    std::string return_current_datetime()
    {
        // 現在日時を文字列で返す
        auto now = std::chrono::system_clock::now();
        std::time_t in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        std::tm jit;
#ifdef WIN32
        errno_t error = localtime_s(&jit, &in_time_t);
#else
        jit = *std::localtime(&in_time_t);
#endif
        ss << std::put_time(&jit, "%c");
        return ss.str();
    }
}