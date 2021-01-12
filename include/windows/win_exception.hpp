#ifndef __IS_WIN_EXCEPTION_HPP__
#define __IS_WIN_EXCEPTION_HPP__

#include "pch.hpp"

namespace Is
{
    /**
     * WIN32 API のエラーを補足してメッセージダイアログで通知.
     * */
    void show_win32api_error(HWND hWnd, LPCTSTR win_name);
}

#endif // __WIN_EXCEPTION_HPP__