#ifndef JETC_LIST_H
#define JETC_LIST_H
#include <stdio.h>
#include <stdlib.h>

#define JETLIST_VPS_USE
#ifdef JETLIST_VPS_USE
typedef struct{
    void*value;
    long long int size;
}jetelement;
jetelement jetElement(void* value,long long int size){
    return (jetelement){value,size};
}
#else
typedef jetelement jetelement;
#endif

typedef struct{
    jetelement *pointer;
    long long int len;
}jetlist;
#define jetListVP(type,value,name) type*name = (type*)malloc(sizeof(type));*name = value;
#define jetListVPV(type,_value) (*((type*)_value.value))
#define jetListVPVI(type,name,i) (*((type*)name.pointer[i].value))
jetlist jetList(){
    return (jetlist){0,0};
}
jetlist jetListArray(jetelement*elements, long long int len){
    jetlist list = jetList();
    list.len = len;
    list.pointer = (jetelement*) malloc(len*sizeof(jetelement));
    for (long long int i = 0; i < len; ++i) {
        list.pointer[i]=elements[i];
    }
    return list;
}
void jetListAppend(jetlist *list,jetelement element){
    jetelement* buf=list->pointer;
    list->len++;
    list->pointer=(jetelement*)malloc(list->len*sizeof(jetelement));
    for (long long int i = 0; i < list->len-1; ++i) {
        list->pointer[i]=buf[i];
    }
    list->pointer[list->len-1]=element;
}

void jetListAdd(jetlist *list,jetelement element,long long int index){
    if(index>=list->len){
        printf("<Index> >= <List.Len> %d >= %d\n", (int)(__int64)index, (int)(__int64)list->len);
        printf("<Error::Index out of bounds>");
        exit(1);
    }
    jetelement* buf=list->pointer;
    list->len++;
    list->pointer=(jetelement*)malloc(list->len*sizeof(jetelement));
    long long int offset =0;
    for (long long int i = 0; i < list->len-1; ++i) {
        if(i==index){
            list->pointer[i]=element;
            offset++;
        }
        list->pointer[i+offset]=buf[i];
    }
}
jetlist jetListMerge(jetlist list1, jetlist list2){
    jetlist list = jetList();
    list.len=list1.len+list2.len;
    list.pointer=(jetelement*) malloc(sizeof(jetelement)*list.len);
    for (long long int i = 0; i < list1.len; ++i) {
        list.pointer[i]=list1.pointer[i];
    }
    for (long long int i = 0; i < list1.len; ++i) {
        list.pointer[list1.len+i]=list2.pointer[i];
    }
    return list;
}
void jetListRemove(jetlist *list,long long int index){
    if(index>=list->len){
        printf("<Index> >= <List.Len> %d >= %d\n", (int)(__int64)index, (int)(__int64)list->len);
        printf("<Error::Index out of bounds>");
        exit(1);
    }
    jetelement* buf = list->pointer;
    list->len--;
    list->pointer=(jetelement*) malloc(list->len*sizeof(jetelement));
    for (long long int i = 0; i < index; ++i) {
        list->pointer[i]=buf[i];
    }
    for (long long int i = index; i < list->len ; ++i) {
        list->pointer[i]=buf[i+1];
    }
}
jetlist jetListWithout(jetlist list, long long int index){
    jetlist buf = list;
    jetListRemove(&buf,index);
    return buf;
}
jetlist jetListSlice(jetlist list, long long int index1, long long int index2){
    if(index2<index1||index2>=list.len){
        printf("<Index2> < <Index1> %d < %d \n<Index2> >= <List.Len> %d >= %d", (int)(__int64)index2,(int)(__int64)index1,(int)(__int64)index2,(int)(__int64)list.len);
        printf("<Error::Index out of bounds>");
        exit(1);
    }
    jetelement* buf = list.pointer;
    jetlist listbuf = list;
    listbuf.len-=index2-index1+1;
    list.pointer=(jetelement*) malloc((list.len*sizeof(jetelement)));
    long long int offset = 0;
    for (long long int i = 0; i < listbuf.len; ++i) {
        if(i==index1){
            offset=index2-index1+1;
        }
        list.pointer[i]=buf[i+offset];
    }
    return listbuf;
}
#endif