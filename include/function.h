#ifndef _FUNCTION_H
#define _FUNCTION_H



LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);


//
//// 初始化计时器频率
//void initializeTimer(LARGE_INTEGER* frequency);
//
//// 获取当前时间戳
//long getCurrentTimestamp(LARGE_INTEGER* frequency);
//
//// 打印按键时间戳信息
//void printTimestamp(char key, char* action, long timestamp);
//
//// 按键记录逻辑
//void recordKeystrokes(LARGE_INTEGER* frequency);


//////////老版本//////////////

//
//// 函数原型
//void waitForAnyKey();
//double getElapsedTime(LARGE_INTEGER startTime, LARGE_INTEGER frequency);
//void monitorKeyPress();




//以下为调用windows HOOK

//double GetKeyPressTimestamp();
//
//LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);//记录键盘按下时间戳
//
//HHOOK SetKeyboardHook();//设置HOOK事件
//
//void MessageLoop(HHOOK hook);//

#endif // !_FUNCTION_H

