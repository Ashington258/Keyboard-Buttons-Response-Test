#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>


#include <iostream>

// 回调函数，用于处理按键事件
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    static DWORD startTime = 0;

    if (nCode >= 0)
    {
        // 按下按键
        if (wParam == WM_KEYDOWN)
        {
            KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;
            DWORD keyCode = kbStruct->vkCode;
            DWORD timestamp = GetTickCount() - startTime;
            char charCode = MapVirtualKeyA(keyCode, MAPVK_VK_TO_CHAR);
            std::cout << "按下按键：" << charCode << "，时间戳：" << timestamp << "ms" << std::endl;
        }
        // 松开按键
        else if (wParam == WM_KEYUP)
        {
            KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;
            DWORD keyCode = kbStruct->vkCode;
            DWORD timestamp = GetTickCount() - startTime;
            char charCode = MapVirtualKeyA(keyCode, MAPVK_VK_TO_CHAR);
            std::cout << "松开按键：" << charCode << "，时间戳：" << timestamp << "ms" << std::endl;
        }
    }
    else if (nCode == HC_ACTION && wParam == WM_SYSKEYDOWN)
    {
        // 开始计时
        startTime = GetTickCount();
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}





//
//// 初始化计时器频率
//void initializeTimer(LARGE_INTEGER* frequency) {
//    QueryPerformanceFrequency(frequency);
//}
//
//// 获取当前时间戳
//long getCurrentTimestamp(LARGE_INTEGER* frequency, LARGE_INTEGER* start_time) {
//    LARGE_INTEGER current_time;
//    QueryPerformanceCounter(&current_time);
//    return (long)(((double)current_time.QuadPart - (double)start_time->QuadPart) * 1000.0 / frequency->QuadPart);
//}
//
//// 打印按键时间戳信息
//void printTimestamp(char key, const char* action, long timestamp) {
//    printf("按下的按键: %c\n", key);
//    printf("操作: %s\n", action);
//    printf("时间戳: %ldms\n\n", timestamp);
//}
//
//// 按键记录逻辑
//void recordKeystrokes(LARGE_INTEGER* frequency) {
//    int key;
//    long start_time, end_time;
//    LARGE_INTEGER start_counter;
//    LARGE_INTEGER current_counter;
//    int is_key_down = 0;
//
//    printf("按下按键开始记录，按下ESC退出。\n");
//
//    // 获取起始时间戳和计数器
//    QueryPerformanceCounter(&start_counter);
//    start_time = getCurrentTimestamp(frequency, &start_counter);
//
//    while (1) {
//        if (_kbhit()) {
//            key = _getch();
//            if (key == 27) {
//                printf("\n程序已退出。\n");
//                break;
//            }
//
//            if (!is_key_down) {
//                is_key_down = 1;
//                end_time = getCurrentTimestamp(frequency, &start_counter);
//                printTimestamp(key, "按下", end_time);
//            }
//        }
//        else {
//            if (is_key_down) {
//                is_key_down = 0;
//                end_time = getCurrentTimestamp(frequency, &start_counter);
//                printTimestamp(key, "弹起", end_time);
//            }
//        }
//    }
//}
//
//int main() {
//    LARGE_INTEGER frequency;
//
//    initializeTimer(&frequency);
//    recordKeystrokes(&frequency);
//
//    return 0;
//}
//
//
//
////////////////////////////////////老版本/////////////////////////////////////////

//
//
//// 等待用户按下任意键
//void waitForAnyKey()
//{
//    HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
//    INPUT_RECORD inputRec;
//    DWORD numEventsRead;
//
//    ReadConsoleInput(hConsoleIn, &inputRec, 1, &numEventsRead);
//    while (inputRec.EventType != KEY_EVENT || !inputRec.Event.KeyEvent.bKeyDown)
//    {
//        ReadConsoleInput(hConsoleIn, &inputRec, 1, &numEventsRead);
//    }
//}
//
//// 获取时间差（毫秒）
//double getElapsedTime(LARGE_INTEGER startTime, LARGE_INTEGER frequency)
//{
//    LARGE_INTEGER currentTime;
//    QueryPerformanceCounter(&currentTime);
//
//    double elapsedMilliseconds = (double)(currentTime.QuadPart - startTime.QuadPart) / frequency.QuadPart * 1000;
//
//    return elapsedMilliseconds;
//}
//
//// 监视键盘按键事件
//void monitorKeyPress()
//{
//    HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
//    INPUT_RECORD inputRec;
//    DWORD numEventsRead;
//
//    LARGE_INTEGER frequency;
//    LARGE_INTEGER startTime;
//    QueryPerformanceFrequency(&frequency);
//    QueryPerformanceCounter(&startTime);
//
//    while (1)
//    {
//        if (ReadConsoleInput(hConsoleIn, &inputRec, 1, &numEventsRead))
//        {
//            if (inputRec.EventType == KEY_EVENT)
//            {
//                if (inputRec.Event.KeyEvent.bKeyDown)
//                {
//                    if (inputRec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
//                    {
//                        break;
//                    }
//                    else
//                    {
//                        // 获取按键按下时间戳
//                        double pressTime = getElapsedTime(startTime, frequency);
//
//                        printf("Key '%c' pressed at %.3f milliseconds\n", inputRec.Event.KeyEvent.uChar.AsciiChar, pressTime);
//                    }
//                }
//                else
//                {
//                    // 获取按键抬起时间戳
//                    double releaseTime = getElapsedTime(startTime, frequency);
//
//                    printf("Key '%c' released at %.3f milliseconds\n", inputRec.Event.KeyEvent.uChar.AsciiChar, releaseTime);
//                }
//            }
//        }
//    }
//}
//
//
//
//
//double GetKeyPressTimestamp()
//{
//    // 获取当前时钟的频率
//    LARGE_INTEGER frequency;
//    QueryPerformanceFrequency(&frequency);
//
//    // 获取按下键盘瞬间的时间戳
//    LARGE_INTEGER timestamp;
//    QueryPerformanceCounter(&timestamp);
//
//    // 将时间戳转换为毫秒
//    double milliseconds = (timestamp.QuadPart * 1000.0) / frequency.QuadPart;
//
//    return milliseconds;
//}

///*
//**********************************用于获取键盘按下的时间戳***************************************** 
//
//LRESULT 是 Windows API 中定义的一个数据类型，用于表示函数的返回值。它是一个长整型（long）的别名。
//
//CALLBACK 是一个宏定义，在 Windows API 中用于声明回调函数的类型。(调用约定)
//
//code 是钩子代码，表示当前的钩子事件类型。在这里，我们检查 code 是否等于 HC_ACTION，它表示钩子事件需要进行处理。
//HC_ACTION 是一个常量，表示钩子事件的类型为动作事件。
//wParam 是一个参数，它包含了发送给回调函数的消息的附加信息。在这里，我们检查 wParam 是否等于 WM_KEYDOWN，它表示收到了键盘按下的消息。
//如果上述两个条件都满足，说明我们捕获到了键盘按下的事件。
//GetTickCount() 函数用于获取当前系统时间的时间戳，以毫秒为单位。它返回一个 DWORD 类型的值，表示当前的时间戳。
//我们将获取到的时间戳存储在名为 timestamp 的变量中。
//最后，我们使用 printf 函数将时间戳打印出来，用于显示按下键盘的时间戳信息。
//综上，这段代码的作用是在键盘按下的事件发生时，获取当前的时间戳并将其打印出来，以记录按下键盘的时间。
//*/
//LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
//    if (code == HC_ACTION) {
//        if (wParam == WM_KEYDOWN) {
//            DWORD timestamp = GetTickCount(); // 获取当前时间戳
//            printf("按下键盘：时间戳：%lu\n", timestamp);
//        }
//    }
//    return CallNextHookEx(NULL, code, wParam, lParam);
//}
///*
//*******************************设置一个HOOK，用于处理键盘事件*************************************
//
//SetKeyboardHook 是函数的名称，它的返回类型为 HHOOK，表示返回一个钩子句柄。
//在函数体内部，我们使用 SetWindowsHookEx 函数来设置键盘钩子。参数 WH_KEYBOARD_LL 表示我们要设置的是键盘的低级钩子。
//KeyboardProc 是钩子过程的回调函数，用于处理键盘事件。
//NULL 表示我们要监视系统中的所有线程。最后一个参数为 0，表示将钩子关联到当前的线程。
//如果设置钩子失败（返回的钩子句柄为 NULL），则输出一条错误信息表示无法设置键盘钩子。
//最后，返回钩子句柄 hook。
//这段代码的作用是封装了设置键盘钩子的过程，并返回了设置好的钩子句柄。
//在其他地方调用 SetKeyboardHook 函数时，可以获取到键盘钩子的句柄，以便后续的操作，比如传递给消息循环函数进行事件处理。
//需要注意的是，在使用完钩子后，记得调用 UnhookWindowsHookEx 函数解除钩子，以释放相关资源。
//https://blog.csdn.net/weixin_39345003/article/details/80813803
//*/
//HHOOK SetKeyboardHook() {
//    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
//    if (hook == NULL) {
//        printf("无法设置键盘钩子\n");
//    }
//    return hook;
//}
//
//void MessageLoop(HHOOK hook) {
//    MSG msg;
//    while (GetMessage(&msg, NULL, 0, 0) > 0) {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//    UnhookWindowsHookEx(hook);
//}
//
////*************以下程序使用原生clock计时器精度有限***************//
// 
//#include <stdio.h>
//#include <stdlib.h>
//#include <conio.h>
//#include <time.h>
//
//int main() {
//    int key;
//    clock_t start_time, end_time;
//
//    printf("按下按键开始记录，按下ESC退出。\n");
//
//    while (1) {
//        if (_kbhit()) {
//            key = _getch();
//            if (key == 27) {  // ESC键的ASCII码为27
//                printf("\n程序已退出。\n");
//                break;
//            }
//
//            start_time = clock();
//            printf("按下的按键: %c\n", key);
//            printf("操作: 按下\n");
//            printf("时间戳: %ldms\n\n", start_time);
//        }
//
//        if (_kbhit()) {
//            key = _getch();
//            if (key == 27) {
//                printf("\n程序已退出。\n");
//                break;
//            }
//
//            end_time = clock();
//            printf("按下的按键: %c\n", key);
//            printf("操作: 弹起\n");
//            printf("时间戳: %ldms\n\n", end_time);
//        }
//    }
//
//    return 0;
//}
//
//


//int main()
//{
//    printf("Press any key to start...\n");
//    waitForAnyKey();
//
//    printf("Press 'ESC' to stop...\n");
//    monitorKeyPress();
//
//    return 0;
//}

