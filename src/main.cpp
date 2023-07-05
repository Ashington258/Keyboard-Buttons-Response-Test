#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include"function.h"

int main() {
    LARGE_INTEGER frequency;

    initializeTimer(&frequency);
    recordKeystrokes(&frequency);

    return 0;
}

