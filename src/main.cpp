#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include"function.h"





int main() {
    LARGE_INTEGER frequency;

    initializeTimer(&frequency);
    recordKeystrokes(&frequency);

    return 0;
}

