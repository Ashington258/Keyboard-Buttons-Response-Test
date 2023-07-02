#include <stdio.h>
#include <windows.h>

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
    if (code == HC_ACTION) {
        if (wParam == WM_KEYDOWN) {
            DWORD timestamp = GetTickCount(); // ��ȡ��ǰʱ���
            printf("���¼��̣�ʱ�����%lu\n", timestamp);
        }
    }
    return CallNextHookEx(NULL, code, wParam, lParam);
}

int main() {
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hook == NULL) {
        printf("�޷����ü��̹���\n");
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hook);
    return 0;
}
