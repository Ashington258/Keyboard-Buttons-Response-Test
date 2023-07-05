#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>


#include <iostream>

// �ص����������ڴ������¼�
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    static DWORD startTime = 0;

    if (nCode >= 0)
    {
        // ���°���
        if (wParam == WM_KEYDOWN)
        {
            KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;
            DWORD keyCode = kbStruct->vkCode;
            DWORD timestamp = GetTickCount() - startTime;
            char charCode = MapVirtualKeyA(keyCode, MAPVK_VK_TO_CHAR);
            std::cout << "���°�����" << charCode << "��ʱ�����" << timestamp << "ms" << std::endl;
        }
        // �ɿ�����
        else if (wParam == WM_KEYUP)
        {
            KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;
            DWORD keyCode = kbStruct->vkCode;
            DWORD timestamp = GetTickCount() - startTime;
            char charCode = MapVirtualKeyA(keyCode, MAPVK_VK_TO_CHAR);
            std::cout << "�ɿ�������" << charCode << "��ʱ�����" << timestamp << "ms" << std::endl;
        }
    }
    else if (nCode == HC_ACTION && wParam == WM_SYSKEYDOWN)
    {
        // ��ʼ��ʱ
        startTime = GetTickCount();
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}





//
//// ��ʼ����ʱ��Ƶ��
//void initializeTimer(LARGE_INTEGER* frequency) {
//    QueryPerformanceFrequency(frequency);
//}
//
//// ��ȡ��ǰʱ���
//long getCurrentTimestamp(LARGE_INTEGER* frequency, LARGE_INTEGER* start_time) {
//    LARGE_INTEGER current_time;
//    QueryPerformanceCounter(&current_time);
//    return (long)(((double)current_time.QuadPart - (double)start_time->QuadPart) * 1000.0 / frequency->QuadPart);
//}
//
//// ��ӡ����ʱ�����Ϣ
//void printTimestamp(char key, const char* action, long timestamp) {
//    printf("���µİ���: %c\n", key);
//    printf("����: %s\n", action);
//    printf("ʱ���: %ldms\n\n", timestamp);
//}
//
//// ������¼�߼�
//void recordKeystrokes(LARGE_INTEGER* frequency) {
//    int key;
//    long start_time, end_time;
//    LARGE_INTEGER start_counter;
//    LARGE_INTEGER current_counter;
//    int is_key_down = 0;
//
//    printf("���°�����ʼ��¼������ESC�˳���\n");
//
//    // ��ȡ��ʼʱ����ͼ�����
//    QueryPerformanceCounter(&start_counter);
//    start_time = getCurrentTimestamp(frequency, &start_counter);
//
//    while (1) {
//        if (_kbhit()) {
//            key = _getch();
//            if (key == 27) {
//                printf("\n�������˳���\n");
//                break;
//            }
//
//            if (!is_key_down) {
//                is_key_down = 1;
//                end_time = getCurrentTimestamp(frequency, &start_counter);
//                printTimestamp(key, "����", end_time);
//            }
//        }
//        else {
//            if (is_key_down) {
//                is_key_down = 0;
//                end_time = getCurrentTimestamp(frequency, &start_counter);
//                printTimestamp(key, "����", end_time);
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
////////////////////////////////////�ϰ汾/////////////////////////////////////////

//
//
//// �ȴ��û����������
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
//// ��ȡʱ�����룩
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
//// ���Ӽ��̰����¼�
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
//                        // ��ȡ��������ʱ���
//                        double pressTime = getElapsedTime(startTime, frequency);
//
//                        printf("Key '%c' pressed at %.3f milliseconds\n", inputRec.Event.KeyEvent.uChar.AsciiChar, pressTime);
//                    }
//                }
//                else
//                {
//                    // ��ȡ����̧��ʱ���
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
//    // ��ȡ��ǰʱ�ӵ�Ƶ��
//    LARGE_INTEGER frequency;
//    QueryPerformanceFrequency(&frequency);
//
//    // ��ȡ���¼���˲���ʱ���
//    LARGE_INTEGER timestamp;
//    QueryPerformanceCounter(&timestamp);
//
//    // ��ʱ���ת��Ϊ����
//    double milliseconds = (timestamp.QuadPart * 1000.0) / frequency.QuadPart;
//
//    return milliseconds;
//}

///*
//**********************************���ڻ�ȡ���̰��µ�ʱ���***************************************** 
//
//LRESULT �� Windows API �ж����һ���������ͣ����ڱ�ʾ�����ķ���ֵ������һ�������ͣ�long���ı�����
//
//CALLBACK ��һ���궨�壬�� Windows API �����������ص����������͡�(����Լ��)
//
//code �ǹ��Ӵ��룬��ʾ��ǰ�Ĺ����¼����͡���������Ǽ�� code �Ƿ���� HC_ACTION������ʾ�����¼���Ҫ���д���
//HC_ACTION ��һ����������ʾ�����¼�������Ϊ�����¼���
//wParam ��һ���������������˷��͸��ص���������Ϣ�ĸ�����Ϣ����������Ǽ�� wParam �Ƿ���� WM_KEYDOWN������ʾ�յ��˼��̰��µ���Ϣ��
//��������������������㣬˵�����ǲ����˼��̰��µ��¼���
//GetTickCount() �������ڻ�ȡ��ǰϵͳʱ���ʱ������Ժ���Ϊ��λ��������һ�� DWORD ���͵�ֵ����ʾ��ǰ��ʱ�����
//���ǽ���ȡ����ʱ����洢����Ϊ timestamp �ı����С�
//�������ʹ�� printf ������ʱ�����ӡ������������ʾ���¼��̵�ʱ�����Ϣ��
//���ϣ���δ�����������ڼ��̰��µ��¼�����ʱ����ȡ��ǰ��ʱ����������ӡ�������Լ�¼���¼��̵�ʱ�䡣
//*/
//LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
//    if (code == HC_ACTION) {
//        if (wParam == WM_KEYDOWN) {
//            DWORD timestamp = GetTickCount(); // ��ȡ��ǰʱ���
//            printf("���¼��̣�ʱ�����%lu\n", timestamp);
//        }
//    }
//    return CallNextHookEx(NULL, code, wParam, lParam);
//}
///*
//*******************************����һ��HOOK�����ڴ�������¼�*************************************
//
//SetKeyboardHook �Ǻ��������ƣ����ķ�������Ϊ HHOOK����ʾ����һ�����Ӿ����
//�ں������ڲ�������ʹ�� SetWindowsHookEx ���������ü��̹��ӡ����� WH_KEYBOARD_LL ��ʾ����Ҫ���õ��Ǽ��̵ĵͼ����ӡ�
//KeyboardProc �ǹ��ӹ��̵Ļص����������ڴ�������¼���
//NULL ��ʾ����Ҫ����ϵͳ�е������̡߳����һ������Ϊ 0����ʾ�����ӹ�������ǰ���̡߳�
//������ù���ʧ�ܣ����صĹ��Ӿ��Ϊ NULL���������һ��������Ϣ��ʾ�޷����ü��̹��ӡ�
//��󣬷��ع��Ӿ�� hook��
//��δ���������Ƿ�װ�����ü��̹��ӵĹ��̣������������úõĹ��Ӿ����
//�������ط����� SetKeyboardHook ����ʱ�����Ի�ȡ�����̹��ӵľ�����Ա�����Ĳ��������紫�ݸ���Ϣѭ�����������¼�����
//��Ҫע����ǣ���ʹ���깳�Ӻ󣬼ǵõ��� UnhookWindowsHookEx ����������ӣ����ͷ������Դ��
//https://blog.csdn.net/weixin_39345003/article/details/80813803
//*/
//HHOOK SetKeyboardHook() {
//    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
//    if (hook == NULL) {
//        printf("�޷����ü��̹���\n");
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
////*************���³���ʹ��ԭ��clock��ʱ����������***************//
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
//    printf("���°�����ʼ��¼������ESC�˳���\n");
//
//    while (1) {
//        if (_kbhit()) {
//            key = _getch();
//            if (key == 27) {  // ESC����ASCII��Ϊ27
//                printf("\n�������˳���\n");
//                break;
//            }
//
//            start_time = clock();
//            printf("���µİ���: %c\n", key);
//            printf("����: ����\n");
//            printf("ʱ���: %ldms\n\n", start_time);
//        }
//
//        if (_kbhit()) {
//            key = _getch();
//            if (key == 27) {
//                printf("\n�������˳���\n");
//                break;
//            }
//
//            end_time = clock();
//            printf("���µİ���: %c\n", key);
//            printf("����: ����\n");
//            printf("ʱ���: %ldms\n\n", end_time);
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

