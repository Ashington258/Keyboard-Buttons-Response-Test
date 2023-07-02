#include <stdio.h>
#include <windows.h>

/*
**********************************���ڻ�ȡ���̰��µ�ʱ���***************************************** 

LRESULT �� Windows API �ж����һ���������ͣ����ڱ�ʾ�����ķ���ֵ������һ�������ͣ�long���ı�����

CALLBACK ��һ���궨�壬�� Windows API �����������ص����������͡�(����Լ��)

code �ǹ��Ӵ��룬��ʾ��ǰ�Ĺ����¼����͡���������Ǽ�� code �Ƿ���� HC_ACTION������ʾ�����¼���Ҫ���д���
HC_ACTION ��һ����������ʾ�����¼�������Ϊ�����¼���
wParam ��һ���������������˷��͸��ص���������Ϣ�ĸ�����Ϣ����������Ǽ�� wParam �Ƿ���� WM_KEYDOWN������ʾ�յ��˼��̰��µ���Ϣ��
��������������������㣬˵�����ǲ����˼��̰��µ��¼���
GetTickCount() �������ڻ�ȡ��ǰϵͳʱ���ʱ������Ժ���Ϊ��λ��������һ�� DWORD ���͵�ֵ����ʾ��ǰ��ʱ�����
���ǽ���ȡ����ʱ����洢����Ϊ timestamp �ı����С�
�������ʹ�� printf ������ʱ�����ӡ������������ʾ���¼��̵�ʱ�����Ϣ��
���ϣ���δ�����������ڼ��̰��µ��¼�����ʱ����ȡ��ǰ��ʱ����������ӡ�������Լ�¼���¼��̵�ʱ�䡣
*/
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
    if (code == HC_ACTION) {
        if (wParam == WM_KEYDOWN) {
            DWORD timestamp = GetTickCount(); // ��ȡ��ǰʱ���
            printf("���¼��̣�ʱ�����%lu\n", timestamp);
        }
    }
    return CallNextHookEx(NULL, code, wParam, lParam);
}
/*
*******************************����һ��HOOK�����ڴ�������¼�*************************************

SetKeyboardHook �Ǻ��������ƣ����ķ�������Ϊ HHOOK����ʾ����һ�����Ӿ����
�ں������ڲ�������ʹ�� SetWindowsHookEx ���������ü��̹��ӡ����� WH_KEYBOARD_LL ��ʾ����Ҫ���õ��Ǽ��̵ĵͼ����ӡ�
KeyboardProc �ǹ��ӹ��̵Ļص����������ڴ�������¼���
NULL ��ʾ����Ҫ����ϵͳ�е������̡߳����һ������Ϊ 0����ʾ�����ӹ�������ǰ���̡߳�
������ù���ʧ�ܣ����صĹ��Ӿ��Ϊ NULL���������һ��������Ϣ��ʾ�޷����ü��̹��ӡ�
��󣬷��ع��Ӿ�� hook��
��δ���������Ƿ�װ�����ü��̹��ӵĹ��̣������������úõĹ��Ӿ����
�������ط����� SetKeyboardHook ����ʱ�����Ի�ȡ�����̹��ӵľ�����Ա�����Ĳ��������紫�ݸ���Ϣѭ�����������¼�����
��Ҫע����ǣ���ʹ���깳�Ӻ󣬼ǵõ��� UnhookWindowsHookEx ����������ӣ����ͷ������Դ��
https://blog.csdn.net/weixin_39345003/article/details/80813803
*/
HHOOK SetKeyboardHook() {
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hook == NULL) {
        printf("�޷����ü��̹���\n");
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

