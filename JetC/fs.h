#ifndef JETC_FS_H
#define JETC_FS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



bool jetFileExists(char*filename){
    FILE *f=fopen(filename,"r");
    bool out = f!=NULL;
    return out;
}
char*jetFileReadAll(char*filename,size_t *size){
    FILE*f=fopen(filename,"rb");
    if(f==NULL){
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    *size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char*buf = (char*) malloc(*size*sizeof(char));
    fread(buf, 1,*size, f);
    fclose(f);
    return buf;
}

#endif