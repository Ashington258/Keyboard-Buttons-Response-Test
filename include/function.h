#ifndef _FUNCTION_H
#define _FUNCTION_H



LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);


//
//// ��ʼ����ʱ��Ƶ��
//void initializeTimer(LARGE_INTEGER* frequency);
//
//// ��ȡ��ǰʱ���
//long getCurrentTimestamp(LARGE_INTEGER* frequency);
//
//// ��ӡ����ʱ�����Ϣ
//void printTimestamp(char key, char* action, long timestamp);
//
//// ������¼�߼�
//void recordKeystrokes(LARGE_INTEGER* frequency);


//////////�ϰ汾//////////////

//
//// ����ԭ��
//void waitForAnyKey();
//double getElapsedTime(LARGE_INTEGER startTime, LARGE_INTEGER frequency);
//void monitorKeyPress();




//����Ϊ����windows HOOK

//double GetKeyPressTimestamp();
//
//LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);//��¼���̰���ʱ���
//
//HHOOK SetKeyboardHook();//����HOOK�¼�
//
//void MessageLoop(HHOOK hook);//

#endif // !_FUNCTION_H

