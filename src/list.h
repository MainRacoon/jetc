#ifndef JETC_LIST_H
#define JETC_LIST_H
#include <stdio.h>
#include <stdlib.h>

#define JETLIST_VPS_USE
#ifdef JETLIST_VPS_USE
typedef struct{
    void*value;
    size_t size;
}jetelement;
jetelement jetElement(void* value,size_t size){
    return (jetelement){value,size};
}
#else
typedef jetelement jetelement;
#endif

typedef struct{
    jetelement *pointer;
    size_t len;
}jetlist;
#define jetListVoidPointer(type,value) &(type[]){value}
#define jetListVoidPValue(type,value) ((type*)value)[0]

jetlist jetList(){
    return (jetlist){(jetelement*){},0};
}
void jetListAppend(jetlist *list,jetelement element){
    jetelement* buf=list->pointer;
    list->len++;
    list->pointer=(jetelement*)malloc(list->len*sizeof(jetelement));
    for (size_t i = 0; i < list->len-1; ++i) {
        list->pointer[i]=buf[i];
    }
    list->pointer[list->len-1]=element;
}

void jetListAdd(jetlist *list,jetelement element,size_t index){
    if(index>=list->len){
        printf("<Index> >= <List.Len> %d >= %d\n", (int)(intptr_t)index, (int)(intptr_t)list->len);
        printf("<Error::Index out of bounds>");
        exit(1);
    }
    jetelement* buf=list->pointer;
    list->len++;
    list->pointer=(jetelement*)malloc(list->len*sizeof(jetelement));
    size_t offset =0;
    for (size_t i = 0; i < list->len-1; ++i) {
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
    for (size_t i = 0; i < list1.len; ++i) {
        list.pointer[i]=list1.pointer[i];
    }
    for (size_t i = 0; i < list1.len; ++i) {
        list.pointer[list1.len+i]=list2.pointer[i];
    }
    return list;
}
void jetListRemove(jetlist *list,size_t index){
    if(index>=list->len){
        printf("<Index> >= <List.Len> %d >= %d\n", (int)(intptr_t)index, (int)(intptr_t)list->len);
        printf("<Error::Index out of bounds>");
        exit(1);
    }
    jetelement* buf = list->pointer;
    list->len--;
    list->pointer=(jetelement*) malloc(list->len*sizeof(jetelement));
    for (size_t i = 0; i < index; ++i) {
        list->pointer[i]=buf[i];
    }
    for (size_t i = index; i < list->len ; ++i) {
        list->pointer[i]=buf[i+1];
    }
}
jetlist jetListWithout(jetlist list, size_t index){
    jetlist buf = list;
    jetListRemove(&buf,index);
    return buf;
}
jetlist jetListSlice(jetlist list, size_t index1, size_t index2){
    if(index2<index1||index2>=list.len){
        printf("<Index2> < <Index1> %d < %d \n<Index2> >= <List.Len> %d >= %d", (int)(intptr_t)index2,(int)(intptr_t)index1,(int)(intptr_t)index2,(int)(intptr_t)list.len);
        printf("<Error::Index out of bounds>");
        exit(1);
    }
    jetelement* buf = list.pointer;
    jetlist listbuf = list;
    listbuf.len-=index2-index1+1;
    list.pointer=(jetelement*) malloc((list.len*sizeof(jetelement)));
    size_t offset = 0;
    for (size_t i = 0; i < listbuf.len; ++i) {
        if(i==index1){
            offset=index2-index1+1;
        }
        list.pointer[i]=buf[i+offset];
    }
    return listbuf;
}
#endif