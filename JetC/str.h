#ifndef JETC_STR_H
#define JETC_STR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
char* jetStrf(const char* format, ...) {
    va_list args;
    va_list args_copy;
    int needed;
    char *buffer;
    va_start(args, format);
    va_copy(args_copy, args);
    needed = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);
    buffer = (char*)malloc(needed);
    if (!buffer) {
        va_end(args_copy);
        return NULL;
    }
    vsnprintf(buffer, needed, format, args_copy);
    va_end(args_copy);
    return buffer;
}
char* jetStrStart(const char* str, char ch) {
    size_t len = strlen(str);
    char *new_str = (char*)malloc(len + 2);
    if (!new_str) {
        return NULL;
    }
    new_str[0] = ch;
    strcpy_s(new_str + 1, len + 1, str);
    return new_str;
}
char* jetStrCat(char* str1, char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t totalLen = len1 + len2;
    char* result = (char*)malloc((totalLen + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';
    if (strcpy_s(result, totalLen + 1, str1) != 0) {
        free(result);
        return NULL;
    }
    if (strcat_s(result, totalLen + 1, str2) != 0) {
        free(result);
        return NULL;
    }
    return result;
}
char* jetStrEnd(const char* str, char ch) {
    size_t len = strlen(str);
    char *new_str = (char*)malloc(len + 2);
    if (!new_str) {
        return NULL;
    }
    strcpy_s(new_str, len + 1, str);
    new_str[len] = ch;
    new_str[len + 1] = '\0';
    return new_str;
}
#endif