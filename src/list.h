#ifndef JETC_LIST_H
#define JETC_LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef void* jetelement;
typedef void**jetarray;
typedef size_t jetsize;

typedef struct jetlist{
    jetarray pointer;
    jetsize len;
}jetlist;
#define jetIntCast(type) (type)(intptr_t)

jetlist jetList(){
    return (jetlist){(jetarray){},0};
}
jetlist jetListArray(jetelement array[],jetsize count){
    jetlist list = jetList();
    list.len=count;
    list.pointer=(jetarray) malloc(sizeof(jetelement)*count);
    for (jetsize i = 0; i < count; ++i) {
        list.pointer[i]=(jetelement)array[i];
    }
    return list;
}

void jetListAppend(jetlist *list,jetelement element){
    jetarray buf=list->pointer;
    list->len++;
    list->pointer=(jetarray)malloc(list->len*sizeof(jetelement));
    for (jetsize i = 0; i < list->len-1; ++i) {
        list->pointer[i]=buf[i];
    }
    list->pointer[list->len-1]=element;
}
void jetListAdd(jetlist *list,jetelement element,jetsize index){
    if(index>=list->len){
        printf("<Index> >= <List.Len> %d >= %d\n", jetIntCast(int)index, jetIntCast(int)list->len);
        printf("<Error::Index out of bounds>");
        exit(1);
    }
    jetarray buf=list->pointer;
    list->len++;
    list->pointer=(jetarray)malloc(list->len*sizeof(jetelement));
    jetsize offset =0;
    for (jetsize i = 0; i < list->len-1; ++i) {
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
    list.pointer=(jetarray) malloc(sizeof(jetelement)*list.len);
    for (jetsize i = 0; i < list1.len; ++i) {
        list.pointer[i]=list1.pointer[i];
    }
    for (jetsize i = 0; i < list1.len; ++i) {
        list.pointer[list1.len+i]=list2.pointer[i];
    }
    return list;
}
void jetListRemove(jetlist *list,jetsize index){
    if(index>=list->len){
        printf("<Index> >= <List.Len> %d >= %d\n", jetIntCast(int)index, jetIntCast(int)list->len);
        printf("<Error::Index out of bounds>");
        exit(1);
    }
    jetarray buf = list->pointer;
    list->len--;
    list->pointer=(jetarray) malloc(list->len*sizeof(jetelement));
    for (jetsize i = 0; i < index; ++i) {
        list->pointer[i]=buf[i];
    }
    for (jetsize i = index; i < list->len ; ++i) {
        list->pointer[i]=buf[i+1];
    }
}
jetlist jetListWithout(jetlist list, jetsize index){
    jetlist buf = list;
    jetListRemove(&buf,index);
    return buf;
}
jetlist jetListSlice(jetlist list, jetsize index1, jetsize index2){
    if(index2<index1||index2>=list.len){
        printf("<Index2> < <Index1> %d < %d \n<Index2> >= <List.Len> %d >= %d", jetIntCast(int)index2,jetIntCast(int)index1,jetIntCast(int)index2,jetIntCast(int)list.len);
        printf("<Error::Index out of bounds>");
        exit(1);
    }
    jetarray buf = list.pointer;
    jetlist listbuf = list;
    listbuf.len-=index2-index1+1;
    list.pointer=(jetarray) malloc((list.len*sizeof(jetelement)));
    jetsize offset = 0;
    for (jetsize i = 0; i < listbuf.len; ++i) {
        if(i==index1){
            offset=index2-index1+1;
        }
        list.pointer[i]=buf[i+offset];
    }
    return listbuf;
}
#endif