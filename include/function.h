#ifndef _FUNCTION_H
#define _FUNCTION_H


/*
用于返回按下按键时的时间戳


*/
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);

HHOOK SetKeyboardHook();

void MessageLoop(HHOOK hook);

#endif // !_FUNCTION_H

