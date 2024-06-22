#ifndef JETC_LIST_H
#define JETC_LIST_H
#include <stdio.h>
#include <stdlib.h>
#define list_u64 unsigned long long
#ifdef JETLIST_VPS_USE
typedef struct{
    void*value;
    list_u64 size;
}jetelement;
jetelement jetElement(void* value,list_u64 size){
    return (jetelement){value,size};
}
jetelement jetElementNS(void*v){
    return jetElement(v,0);
}
#else
typedef void* jetelement;
jetelement jetElement(void* value,list_u64 size){
    return (jetelement)value;
}
#endif

typedef struct{
    jetelement *array;
    list_u64 len;
    list_u64 count;
}jetlist;
#define jetListSizeof(x) sizeof(jetelement)*(x)
jetlist jetList(){
    return (jetlist){0,0,0};
}

void jetListResize(jetlist*list, list_u64 count){
    if(list->len>list->count-count){
        list->len=count;
    }
    list->count= count;
    list->array=(jetelement*) realloc(list->array, jetListSizeof(list->count));
    
}
jetlist jetListArray(jetelement*elements, list_u64 count){
    jetlist list = jetList();
    jetListResize(&list,count);
    list.len=count;
    for (list_u64 i = 0; i < count; ++i) {
        list.array[i]=elements[i];
    }
    return list;
}

void jetListAppend(jetlist *list,jetelement element){
    list->array[list->len]=element;
    list->len++;
}
void jetListAdd(jetlist *list,jetelement element,list_u64 index){
    if(index>=list->len){
        jetListAppend(list,element);
        return;
    }
    for(list_u64 i=list->len;i>index;i++){
        list->array[i]=list->array[i-1];
    }
    list->array[index]=element;
    list->len++;
}
jetlist jetListMerge(jetlist list1, jetlist list2){
    jetlist list = jetList();
    list.len=list1.len+list2.len;
    jetListResize(&list,list1.len+list2.len);
    for(list_u64 i = 0; i<list1.len;i++){
        list.array[i]=list1.array[i];
    }
    for(list_u64 i = 0; i<list2.len;i++){
        list.array[i+list1.len]=list2.array[i];
    }
    return list;
}
int jetListRemove(jetlist *list,list_u64 index){
    if(index>=list->len){
        return 1;
    }
    for (list_u64 i = index; i < list->len-1 ; ++i) {
        list->array[i]=list->array[i+1];
    }
    list->len--;
    return 0;
}
jetlist jetListSlice(jetlist list, list_u64 from, list_u64 to){
    if(from>list.len||to>list.len){
        return jetList();
    }
    list_u64 end,start;
    if(from>to){
        end=from;
        start=to;
    }else{
        end=to;
        start=from;
    }
    jetlist buf = jetList();
    buf.len=end-start+1;
    jetListResize(&buf,buf.len);
    for (list_u64 i = start; i <= end; ++i) {
        buf.array[i-start]=list.array[i];
    }
    return buf;
}
#undef list_u64
#undef jetListSizeof
#endif