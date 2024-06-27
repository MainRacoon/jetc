#ifndef JETC_FS_H
#define JETC_FS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>


#ifdef _WIN32
#include <windows.h>
int jet_FsExists(char *path) {
    DWORD dwAttrib = GetFileAttributes(path);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
            (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}
#else
#include <sys/stat.h>
int jet_FsExists(char *path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

#endif

char**jet_FsList(char*dirname,size_t*count){
    DIR *d;
    struct dirent *dir;
    char **file_list = NULL;
    size_t size = 0;
    size_t capacity = 10;

    file_list = (char **)malloc(capacity * sizeof(char *));
    if (!file_list) {
        return NULL;
    }
    d = opendir(dirname);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
                continue;
            if (size >= capacity) {
                capacity *= 2;
                char **temp = (char **)realloc(file_list, capacity * sizeof(char *));
                if (!temp) {
                    fprintf(stderr, "Memory allocation error\n");
                    for (int i = 0; i < size; ++i) {
                        free(file_list[i]);
                    }
                    free(file_list);
                    closedir(d);
                    return NULL;
                }
                file_list = temp;
            }
            file_list[size] = strdup(dir->d_name);
            if (!file_list[size]) {
                fprintf(stderr, "Memory allocation error\n");
                for (int i = 0; i < size; ++i) {
                    free(file_list[i]);
                }
                free(file_list);
                closedir(d);
                return NULL;
            }

            size++;
        }
        closedir(d);
    }
    *count = size;
    return file_list;
}
char*jet_FsReadAll(char*filename,size_t *size){
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
FILE*jet_FsOverOpen(char*filename,char*mode){
    FILE *f= fopen(filename,"w");
    fprintf(f,"");
    fclose(f);
    f = fopen(filename, mode);
    return f;
}
#endif