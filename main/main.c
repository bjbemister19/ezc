#include "stdio.h"
#include "assert.h"

#include "ezc.h"

int main() {
    const char* file = "/home/brandon/projects/ezc/trash.txt";
    ezfile_write(file, "Testing 1234");
    ezfile_append(file, "\r\nahhhhhhhhh");

    char* data = ezfile_read(file);
    printf("%s\n", data);

    ezfile_delete(file);
    return 0;
}