#ifndef JETC_STR_H
#define JETC_STR_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
char* jet_Strf(const char* format, ...) {
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
char* jet_StrStart(char* str,size_t len, char ch) {
    if(str==NULL){
        return NULL;
    }
    char*buf = (char*)malloc((len+2)*sizeof(char));
    buf[0]=ch;
    for (size_t i = 0; i < len; ++i) {
        buf[i+1]=str[i];
    }
    buf[len+1]=0;
    return buf;
}
char*jet_StrStartA(char*str,char ch){
    return jet_StrStart(str, strlen(str),ch);
}
char* jet_StrCat(char* str1,size_t len1, char* str2,size_t len2) {
    if (str1 == NULL||str2==NULL) {
        return NULL;
    }
    char* buf = (char*)malloc((len1+len2 + 1) * sizeof(char));
    buf[len1+len2] = '\0';
    size_t j = 0;
    for (size_t i = 0; i < len1; ++i) {
        buf[j++]=str1[i];
    }
    for (size_t i = 0; i < len2; ++i) {
        buf[j++]=str2[i];
    }
    return buf;
}
char* jet_StrCatA(char* str1,char* str2){
    return jet_StrCat(str1, strlen(str1),str2, strlen(str2));
}
bool jet_StrCharIs(char*pat,size_t len, char c){
    for (size_t i = 0; i < len; ++i) {
        if(pat[i]==c){
            return true;
        }
    }
    return false;
}
bool jet_StrCharIsA(char*pat, char c){
    return jet_StrCharIs(pat, strlen(pat),c);
}
char* jet_StrEnd(char* str,size_t len, char ch) {
    if(str==NULL){
        return NULL;
    }
    char*buf = (char*)malloc((len+2)*sizeof(char));
    for (size_t i = 0; i < len; ++i) {
        buf[i]=str[i];
    }
    buf[len]=ch;
    buf[len+1]=0;
    return buf;
}
char* jet_StrEndA(char* str, char ch){
    return jet_StrEnd(str, strlen(str),ch);
}
char* jet_StrSub(char *str,size_t len, size_t startIndex, size_t endIndex) {
    if (endIndex >= len) {
        return NULL;
    }
    size_t from = startIndex<endIndex?startIndex:endIndex;
    size_t to = startIndex<endIndex?endIndex:startIndex;
    char *newStr = (char *)malloc((to-from + 1) * sizeof(char));
    for (size_t i =0;i<to-from;i++){
        newStr[i]=str[i+from];
    }
    newStr[to-from] = '\0';
    return newStr;
}
char* jet_StrSubA(char *str,size_t startIndex, size_t endIndex){
    return jet_StrSub(str, strlen(str),startIndex,endIndex);
}
#endif