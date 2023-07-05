#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include"function.h"


int main()
{
    // 设置键盘钩子
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hook == NULL)
    {
        std::cerr << "无法设置键盘钩子" << std::endl;
        return 1;
    }

    // 消息循环，等待键盘事件
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 移除键盘钩子
    UnhookWindowsHookEx(hook);

    return 0;
}


