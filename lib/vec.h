#ifndef VEC_C
#define VEC_C

#include <stddef.h>
#include <stdbool.h>

#define VEC_GROWTH_FACTOR 2
#define VEC_DEFAULT_CAPACITY 1024

typedef void* vec_t;

vec_t vec_new(size_t stride);
vec_t vec_with_capacity(size_t capacity, size_t stride);
void vec_del(vec_t vec);
size_t vec_capacity(vec_t vec);
size_t vec_len(vec_t vec);
bool vec_grow_size(vec_t* vec);
void vec_push(vec_t* vec, void* item);
bool try_vec_push(vec_t* vec, void* item);
void vec_push_to_capacity(vec_t vec, void* item);
bool try_vec_push_to_capacity(vec_t vec, void* item);
void vec_pop(vec_t vec, void* item);
bool try_vec_pop(vec_t vec, void* item);

#endif // VEC_C