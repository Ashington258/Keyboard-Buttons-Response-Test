#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include"function.h"


int main()
{
    // ���ü��̹���
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hook == NULL)
    {
        std::cerr << "�޷����ü��̹���" << std::endl;
        return 1;
    }

    // ��Ϣѭ�����ȴ������¼�
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // �Ƴ����̹���
    UnhookWindowsHookEx(hook);

    return 0;
}


