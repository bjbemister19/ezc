#include "ezfile.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void ezfile_write_internal(FILE* f, const char* data)
{
    int c;
    int i = 0;
    while ((c = data[i]) != '\0') {
        fputc(c, f);
        i++;
    }
}

vec_t ezfile_read(const char* path)
{
    assert(path);

    FILE * f = fopen(path, "r");
    if(!f){
        printf("Failed to open file %s\n", path);
        exit(1);
    }

    size_t file_size = 1;
    char* contents = vec_new(sizeof *contents);

    int c;
    while ((c = fgetc(f)) != EOF) {
        assert((c >> 8) == 0); // Assume 8 bit ASCII only
        char ch = (char)c;
        vec_push((void**)&contents, &ch);
    }

    char nil = '\0';
    vec_push((void**)&contents, &nil);
    
    fclose(f);
    return contents;
}

void ezfile_write(const char* path, const char* data)
{
    assert(path);
    assert(data);

    FILE * f = fopen(path, "w+");
    if(!f){
        printf("Failed to open file %s\n", path);
        exit(1);
    }
    ezfile_write_internal(f, data);
    fclose(f);
}

void ezfile_append(const char* path, const char* data)
{
    assert(path);
    assert(data);

    FILE * f = fopen(path, "a+");
    if(!f){
        printf("Failed to open file %s\n", path);
        exit(1);
    }
    ezfile_write_internal(f, data);
    fclose(f);
}

void ezfile_delete(const char* path)
{
    assert(path);

    remove(path);
}
