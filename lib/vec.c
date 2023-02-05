#include "vec.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

struct vec {
    size_t capacity; 
    size_t stride;
    size_t len;
};

static struct vec* get_ptr_to_header(void* data)
{
    return data - sizeof (struct vec);;
}

static void* get_ptr_to_vec(void* buffer)
{
    return buffer + sizeof (struct vec);
}

static bool has_capacity(void* vec)
{
    struct vec* header = get_ptr_to_header(vec);
    if (header->len >= header->capacity)
        return false;
    return true;
}

static void* get_ptr_to_index(void* vec, size_t index) 
{
    struct vec* header = get_ptr_to_header(vec);
    return vec + (index * header->stride);
}

static void vec_push_internal(void* vec, void* item)
{
    struct vec* header = get_ptr_to_header(vec);
    void* index = get_ptr_to_index(vec, header->len);
    memcpy(index, item, header->stride);
    header->len++;
}

void* vec_new(size_t capacity, size_t stride)
{
    void* buffer = malloc((capacity * stride) + sizeof (struct vec));
    struct vec* header = buffer;
    *header = (struct vec){
        .capacity = capacity,
        .stride = stride,
        .len = 0
    };
    return get_ptr_to_vec(buffer);
}

void vec_del(void* vec)
{
    free(get_ptr_to_header(vec));
}

size_t vec_capacity(void* vec)
{
    struct vec* header = get_ptr_to_header(vec);
    return header->capacity;
}
size_t vec_len(void* vec)
{
    struct vec* header = get_ptr_to_header(vec);
    return header->len;
}

bool vec_grow_size(void** vec) {
    struct vec* header = get_ptr_to_header(*vec);
    void* new = realloc(header, ((header->capacity * VEC_GROWTH_FACTOR) * header->stride) + sizeof (struct vec));
    if (!new) return false;
    header = new;
    header->capacity = header->capacity * VEC_GROWTH_FACTOR;
    *vec = get_ptr_to_vec(new);
    return true;
}

void vec_push(void** vec, void* item)
{
    if(!has_capacity(vec)){
        assert(vec_grow_size(vec));
    }
    vec_push_internal(*vec, item);    
}

bool try_vec_push(void** vec, void* item)
{
    if(!has_capacity(vec)){
        bool success = vec_grow_size(vec);
        if(!success) return false;
    }
    vec_push_internal(*vec, item);  
    return true;
}

void vec_push_to_capacity(void* vec, void* item)
{
    assert(has_capacity(vec));
    vec_push_internal(vec, item);    
}

bool try_vec_push_to_capacity(void* vec, void* item)
{
    if(!has_capacity(vec)) return false;
    vec_push_internal(vec, item);
    return true;
}