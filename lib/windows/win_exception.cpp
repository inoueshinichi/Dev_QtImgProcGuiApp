
#include "win_exception.h"

namespace Is
{
    void show_win32api_error(HWND hWnd, LPCTSTR win_name)
    {
        DWORD errCode = ::GetLastError();
	    LPVOID lpMsgBuff; // エラーメッセージ用バッファポインタ

        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | // テキストのメモリ割り当てを要求
            FORMAT_MESSAGE_FROM_SYSTEM |     // エラーメッセージはWindowsが用意しているものを使用
            FORMAT_MESSAGE_IGNORE_INSERTS,   // 次の引数を無視してエラーコードに対するエラーメッセージを作成する
            NULL,
            errCode,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 言語(日本語)を設定
            (LPTSTR)&lpMsgBuff,                        // メッセージテキストが保存されるバッファへのポインタ
            0,
            NULL
	    );

        MessageBox(hWnd, (LPCTSTR)lpMsgBuff, win_name, MB_OK | MB_ICONINFORMATION);
        LocalFree(lpMsgBuff);
    }
}