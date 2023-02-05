#ifndef VEC_C
#define VEC_C

#include <stddef.h>
#include <stdbool.h>

#define VEC_GROWTH_FACTOR 2

void* vec_new(size_t capacity, size_t stride);
void vec_del(void* vec);
size_t vec_capacity(void* vec);
size_t vec_count(void* vec);
bool vec_grow_size(void** vec);
void vec_push(void** vec, void* item);
bool try_vec_push(void** vec, void* item);
void vec_push_to_capacity(void* vec, void* item);
bool try_vec_push_to_capacity(void* vec, void* item);

#endif // VEC_C