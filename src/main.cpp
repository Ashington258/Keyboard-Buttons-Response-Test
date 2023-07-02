#include <stdio.h>
#include <iostream>
#include <windows.h>
#include"function.h"


// 函数原型
void waitForAnyKey();
double getElapsedTime(LARGE_INTEGER startTime, LARGE_INTEGER frequency);
void monitorKeyPress();

int main()
{
    printf("Press any key to start...\n");
    waitForAnyKey();

    printf("Press 'ESC' to stop...\n");
    monitorKeyPress();

    return 0;
}

// 等待用户按下任意键
void waitForAnyKey()
{
    HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD inputRec;
    DWORD numEventsRead;

    ReadConsoleInput(hConsoleIn, &inputRec, 1, &numEventsRead);
    while (inputRec.EventType != KEY_EVENT || !inputRec.Event.KeyEvent.bKeyDown)
    {
        ReadConsoleInput(hConsoleIn, &inputRec, 1, &numEventsRead);
    }
}

// 获取时间差（毫秒）
double getElapsedTime(LARGE_INTEGER startTime, LARGE_INTEGER frequency)
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);

    double elapsedMilliseconds = (double)(currentTime.QuadPart - startTime.QuadPart) / frequency.QuadPart * 1000;

    return elapsedMilliseconds;
}

// 监视键盘按键事件
void monitorKeyPress()
{
    HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD inputRec;
    DWORD numEventsRead;

    LARGE_INTEGER frequency;
    LARGE_INTEGER startTime;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&startTime);

    double pressStartTime = 0.0;

    while (1)
    {
        if (ReadConsoleInput(hConsoleIn, &inputRec, 1, &numEventsRead))
        {
            if (inputRec.EventType == KEY_EVENT)
            {
                if (inputRec.Event.KeyEvent.bKeyDown)
                {
                    if (inputRec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                    {
                        break;
                    }
                    else if (pressStartTime == 0.0)
                    {
                        // 记录按键按下时间
                        pressStartTime = getElapsedTime(startTime, frequency);
                    }
                }
                else
                {
                    if (pressStartTime != 0.0)
                    {
                        // 计算按键抬起时间差
                        double pressEndTime = getElapsedTime(startTime, frequency);
                        double pressDuration = pressEndTime - pressStartTime;

                        printf("Key released after %.3f milliseconds\n", pressDuration);

                        pressStartTime = 0.0;
                    }
                }
            }
        }
    }
}

