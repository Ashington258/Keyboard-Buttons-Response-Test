#include <stdio.h>
#include <windows.h>
#include"function.h"




int main() {
    HHOOK hook = SetKeyboardHook();
    if (hook != NULL) {
        MessageLoop(hook);
    }
    return 0;
}
