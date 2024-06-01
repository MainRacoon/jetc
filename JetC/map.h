#ifndef JET_MAP_H
#define JET_MAP_H
#include <stdio.h>
#include <stdlib.h>
#include "./list.h"

typedef struct{
    jetlist keys;
    jetlist values;
    size_t len;
}jetmap;

jetmap jetMap(){
    return (jetmap){jetList(),jetList(),0};
}
void jetMapAppend(jetmap*map,jetelement key, jetelement value){
    jetListAppend(&map->keys,key);
    jetListAppend(&map->values,value);
    map->len++;
}
jetmap jetMapMerge(jetmap map1 , jetmap map2){
    jetmap m = jetMap();
    m.keys = jetListMerge(map1.keys, map2.keys);
    m.keys = jetListMerge(map1.keys, map2.keys);
    m.len = map1.len+map2.len;
    return m;
}



#endif