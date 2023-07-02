#include <stdio.h>
#include <windows.h>

/*
**********************************用于获取键盘按下的时间戳***************************************** 

LRESULT 是 Windows API 中定义的一个数据类型，用于表示函数的返回值。它是一个长整型（long）的别名。

CALLBACK 是一个宏定义，在 Windows API 中用于声明回调函数的类型。(调用约定)

code 是钩子代码，表示当前的钩子事件类型。在这里，我们检查 code 是否等于 HC_ACTION，它表示钩子事件需要进行处理。
HC_ACTION 是一个常量，表示钩子事件的类型为动作事件。
wParam 是一个参数，它包含了发送给回调函数的消息的附加信息。在这里，我们检查 wParam 是否等于 WM_KEYDOWN，它表示收到了键盘按下的消息。
如果上述两个条件都满足，说明我们捕获到了键盘按下的事件。
GetTickCount() 函数用于获取当前系统时间的时间戳，以毫秒为单位。它返回一个 DWORD 类型的值，表示当前的时间戳。
我们将获取到的时间戳存储在名为 timestamp 的变量中。
最后，我们使用 printf 函数将时间戳打印出来，用于显示按下键盘的时间戳信息。
综上，这段代码的作用是在键盘按下的事件发生时，获取当前的时间戳并将其打印出来，以记录按下键盘的时间。
*/
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
    if (code == HC_ACTION) {
        if (wParam == WM_KEYDOWN) {
            DWORD timestamp = GetTickCount(); // 获取当前时间戳
            printf("按下键盘：时间戳：%lu\n", timestamp);
        }
    }
    return CallNextHookEx(NULL, code, wParam, lParam);
}
/*
*******************************设置一个HOOK，用于处理键盘事件*************************************

SetKeyboardHook 是函数的名称，它的返回类型为 HHOOK，表示返回一个钩子句柄。
在函数体内部，我们使用 SetWindowsHookEx 函数来设置键盘钩子。参数 WH_KEYBOARD_LL 表示我们要设置的是键盘的低级钩子。
KeyboardProc 是钩子过程的回调函数，用于处理键盘事件。
NULL 表示我们要监视系统中的所有线程。最后一个参数为 0，表示将钩子关联到当前的线程。
如果设置钩子失败（返回的钩子句柄为 NULL），则输出一条错误信息表示无法设置键盘钩子。
最后，返回钩子句柄 hook。
这段代码的作用是封装了设置键盘钩子的过程，并返回了设置好的钩子句柄。
在其他地方调用 SetKeyboardHook 函数时，可以获取到键盘钩子的句柄，以便后续的操作，比如传递给消息循环函数进行事件处理。
需要注意的是，在使用完钩子后，记得调用 UnhookWindowsHookEx 函数解除钩子，以释放相关资源。
https://blog.csdn.net/weixin_39345003/article/details/80813803
*/
HHOOK SetKeyboardHook() {
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hook == NULL) {
        printf("无法设置键盘钩子\n");
    }
    return hook;
}

void MessageLoop(HHOOK hook) {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hook);
}

