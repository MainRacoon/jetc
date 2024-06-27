#ifndef JETC_UTL_H
#define JETC_UTL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
char*jet_UserInput(){
    int bufferSize = 5;
    char *buffer = (char *)malloc(bufferSize * sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }

    int index = 0;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (index > 0) {
                index--;
                printf("\b \b");
            }
        }else if (ch <0) {
            _getch();
            continue;
        } else {
            if (index >= bufferSize - 1) {
                bufferSize *= 2;
                char *newBuffer = (char *)realloc(buffer, bufferSize * sizeof(char));
                if (newBuffer == NULL) {
                    free(buffer);
                    return NULL;
                }
                buffer = newBuffer;
            }
            buffer[index++] = ch;
            putchar(ch);
        }
    }
    buffer[index] = '\0';
    return buffer;
}
void jet_CLS(){
#ifdef _WIN32
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD consoleSize;
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        return;
    }
    consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', consoleSize, coord, &count)) {
        return;
    }
    if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, consoleSize, coord, &count)) {
        return;
    }
    SetConsoleCursorPosition(hStdOut, coord);
#else
    printf("\033[2J\033[H");
    fflush(stdout);
#endif
}
int jet_Random32(){
    return rand();
}
unsigned long long int jet_Random64() {
    unsigned long long int r = 0;
    for (int i=0; i<64; i++) {
        r = r*2 + rand()%2;
    }
    return r;
}
#define jetscmp(x,y) strcmp(x,y)==0
#define jet_SizeOfStr(len) sizeof(char*)*len
#define jet_NumBetween(num,x,y) num% (y - x + 1) + x
#endif

