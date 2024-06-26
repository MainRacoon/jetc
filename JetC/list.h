#ifndef JETC_LIST_H
#define JETC_LIST_H
#include <stdio.h>
#include <stdlib.h>
#define list_u64 unsigned long long
#ifndef JETLIST_VPS_NO
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
#define jet_ListSizeof(x) sizeof(jetelement)*(x)
jetlist jet_List(){
    return (jetlist){0,0,0};
}

void jet_ListResize(jetlist*list, list_u64 elements){
    if(list->len>list->count-elements){
        list->len=elements;
    }
    list->count= elements;
    list->array=(jetelement*) realloc(list->array, jet_ListSizeof(list->count));
    
}
jetlist jet_ListArray(jetelement*elements, list_u64 count){
    jetlist list = jet_List();
    jet_ListResize(&list,count);
    list.len=count;
    for (list_u64 i = 0; i < count; ++i) {
        list.array[i]=elements[i];
    }
    return list;
}
jetelement jet_ListRandom(jetlist list){
    return list.array[jet_Random64(0,list.len-1)];
}
jetlist jet_ListCopy(jetlist list){
    jetlist copy = jet_List();
    jet_ListResize(&copy,list.count);
    copy.len=list.len;
    for (list_u64 i = 0; i < list.len; ++i) {
        jetelement el = (jetelement) malloc(sizeof(jetelement ));
        memcpy(el, list.array[i], sizeof(jetelement));
        copy.array[i]=el;
    }
    return copy;
}
void jet_ListAppend(jetlist *list,jetelement element){
    list->array[list->len]=element;
    list->len++;
}
void jet_ListAdd(jetlist *list,jetelement element,list_u64 index){
    if(index>=list->len){
        jet_ListAppend(list,element);
        return;
    }
    for(list_u64 i=list->len;i>index;i++){
        list->array[i]=list->array[i-1];
    }
    list->array[index]=element;
    list->len++;
}
jetlist jet_ListMerge(list_u64 count, ...){
    va_list ap;
    jetlist buf = jet_List();

    va_start(ap, count);
    for(list_u64 i = 0; i < count; i++) {
        jetlist b = jet_ListCopy(va_arg(ap, jetlist));
        jet_ListResize(&buf, buf.count+b.len);
        list_u64 j = 0;
        while (buf.len!=buf.count){

            buf.array[buf.len]=b.array[j];
            buf.len++;
            j++;
        }
    }
    va_end(ap);

    return buf;
}
int jet_ListRemove(jetlist *list,list_u64 index){
    if(index>=list->len){
        return 1;
    }
    for (list_u64 i = index; i < list->len-1 ; ++i) {
        list->array[i]=list->array[i+1];
    }
    list->len--;
    return 0;
}
jetlist jet_ListSlice(jetlist list, list_u64 from, list_u64 to){
    if(from>list.len||to>list.len){
        return jet_List();
    }
    list_u64 end,start;
    if(from>to){
        end=from;
        start=to;
    }else{
        end=to;
        start=from;
    }
    jetlist buf = jet_List();
    buf.len=end-start+1;
    jet_ListResize(&buf,buf.len);
    for (list_u64 i = start; i <= end; ++i) {
        buf.array[i-start]=list.array[i];
    }
    return buf;
}
#undef list_u64
#undef jet_ListSizeof
#endif