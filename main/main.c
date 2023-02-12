#include "vec.h"
#include "stdio.h"
#include "assert.h"

int main() {
    int* integers = vec_with_capacity(20, sizeof *integers);

    for (int i = 0; i < 11; i++){
        vec_push((void**)&integers, &i);
    }

    vec_reset(integers);

    for (int i = 0; i < vec_len(integers); i++){
        printf("%d, ", integers[i]);
    }
    printf("\n");

    vec_del(integers);
    return 0;
}