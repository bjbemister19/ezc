#include "vec.h"
#include "stdio.h"
#include "assert.h"

int main() {
    int* integers = vec_new(10, sizeof *integers);

    for (int i = 0; i < 11; i++){
        vec_push((void**)&integers, &i);
    }

    for (int i = 0; i < 11; i++){
        printf("%d, ", integers[i]);
    }
    printf("\n");


    vec_del(integers);
    return 0;
}