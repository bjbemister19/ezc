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

static bool has_capacity(vec_t vec)
{
    struct vec* header = get_ptr_to_header(vec);
    if (header->len >= header->capacity)
        return false;
    return true;
}

static bool is_empty(vec_t vec) 
{
    struct vec* header = get_ptr_to_header(vec);
    if(header->len == 0)
        return true;
    return false;
}

static void* get_ptr_to_index(vec_t vec, size_t index) 
{
    struct vec* header = get_ptr_to_header(vec);
    return vec + (index * header->stride);
}

static void vec_push_internal(vec_t vec, void* item)
{
    struct vec* header = get_ptr_to_header(vec);
    void* index = get_ptr_to_index(vec, header->len);
    memcpy(index, item, header->stride);
    header->len++;
}
    
static void vec_pop_internal(vec_t vec, void* item)
{
    struct vec* header = get_ptr_to_header(vec);
    void* index = get_ptr_to_index(vec, header->len-1);
    if(item)
        memcpy(item, index, header->stride);
    header->len--;
}

void* vec_new(size_t stride)
{
    return vec_with_capacity(VEC_DEFAULT_CAPACITY, stride);
}

void* vec_with_capacity(size_t capacity, size_t stride)
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

void vec_del(vec_t vec)
{
    assert(vec);

    free(get_ptr_to_header(vec));
}

void vec_zero(vec_t vec) 
{
    assert(vec);
    
    struct vec* header = get_ptr_to_header(vec);
    memset(vec, 0, header->capacity * header->stride);
    header->len = header->capacity;
}

void vec_zero_rest(vec_t vec) 
{
    assert(vec);

    struct vec* header = get_ptr_to_header(vec);
    void* index = get_ptr_to_index(vec, header->len);
    memset(index, 0, (header->capacity - header->len) * header->stride);
    header->len = header->capacity;
}


void vec_fill(vec_t vec, void* item) 
{
    assert(vec);
    assert(item);

    struct vec* header = get_ptr_to_header(vec);
    header->len = 0;
    for (int i = 0; i < header->capacity; i++){
        vec_push_to_capacity(vec, item);
    }
}

void vec_fill_rest(vec_t vec, void* item)
{
    assert(vec);
    assert(item);

    struct vec* header = get_ptr_to_header(vec);
    for (int i = header->len; i < header->capacity; i++){
        vec_push_to_capacity(vec, item);
    }
}

size_t vec_capacity(vec_t vec)
{
    assert(vec);

    struct vec* header = get_ptr_to_header(vec);
    return header->capacity;
}
size_t vec_len(vec_t vec)
{
    assert(vec);

    struct vec* header = get_ptr_to_header(vec);
    return header->len;
}

void vec_set_len(vec_t vec, size_t new_len)
{
    struct vec* header = get_ptr_to_header(vec);
    header->len = new_len;
}

void vec_grow_size(vec_t* vec) 
{
    assert(try_vec_grow_size(vec));
}

bool try_vec_grow_size(vec_t* vec) {
    assert(vec);
    assert(*vec);

    struct vec* header = get_ptr_to_header(*vec);
    void* new = realloc(header, ((header->capacity * VEC_GROWTH_FACTOR) * header->stride) + sizeof (struct vec));
    if (!new) return false;
    header = new;
    header->capacity = header->capacity * VEC_GROWTH_FACTOR;
    *vec = get_ptr_to_vec(new);
    return true;
}

void vec_push(vec_t* vec, void* item)
{
    assert(vec);
    assert(*vec);
    assert(item);

    if(!has_capacity(vec)){
        vec_grow_size(vec);
    }
    vec_push_internal(*vec, item);    
}

bool try_vec_push(vec_t* vec, void* item)
{
    assert(vec);
    assert(*vec);
    assert(item);

    if(!has_capacity(vec)){
        bool success = try_vec_grow_size(vec);
        if(!success) return false;
    }
    vec_push_internal(*vec, item);  
    return true;
}

void vec_push_to_capacity(vec_t vec, void* item)
{
    assert(vec);
    assert(item);

    assert(has_capacity(vec));
    vec_push_internal(vec, item);    
}

bool try_vec_push_to_capacity(vec_t vec, void* item)
{
    assert(vec);
    assert(item);

    if(!has_capacity(vec)) return false;
    vec_push_internal(vec, item);
    return true;
}

void vec_pop(vec_t vec, void* item)
{
    assert(vec);

    assert(!is_empty(vec));
    vec_pop_internal(vec, item);
}

bool try_vec_pop(vec_t vec, void* item)
{
    assert(vec);

    if(is_empty(vec)) return false;
    vec_pop_internal(vec, item);
    return true;
}

void vec_reset(vec_t vec)
{
    assert(vec);

    struct vec* header = get_ptr_to_header(vec);
    header->len = 0;
}