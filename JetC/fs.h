#ifndef JETC_FS_H
#define JETC_FS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



bool jetFileExists(char*filename){
    FILE *f;
    fopen_s(&f,filename,"r");
    bool out = f!=NULL;
    return out;
}
char*jetFileReadAll(char*filename,size_t *size){
    FILE*f;
    fopen_s(&f,filename,"rb");
    if(f==NULL){
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    *size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char*buf = (char*) malloc(*size*sizeof(char));
    fread_s(buf, *size, 1,*size, f);
    fclose(f);
    return buf;
}

#endif