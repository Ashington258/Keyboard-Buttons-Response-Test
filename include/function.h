#ifndef _FUNCTION_H
#define _FUNCTION_H


/*
���ڷ��ذ��°���ʱ��ʱ���


*/
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);

HHOOK SetKeyboardHook();

void MessageLoop(HHOOK hook);

#endif // !_FUNCTION_H

