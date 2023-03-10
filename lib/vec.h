#ifndef VEC_C
#define VEC_C

#include <stddef.h>
#include <stdbool.h>

#include "eztypes.h"

#define VEC_GROWTH_FACTOR 2
#define VEC_DEFAULT_CAPACITY 1024

/**
 * @brief Create a new vector with default capacity
 * 
 * @note Capacity is how many items the vector is able to store 
 * without re-allocating, the length is zero until values are pushed 
 * into the vector 
 * 
 * Example: `int* integers = vec_new(sizeof *integers);`
 * 
 * @param stride The size of the items to go in the vector
 * @return A new vector of default capacity
 */
vec_t vec_new(size_t stride);

/**
 * @brief Create a new vector with a specified capacity
 * 
 * @note Capacity is how many items the vector is able to store 
 * without re-allocating, the length is zero until values are pushed 
 * into the vector 
 * 
 * Example: `int* integers = vec_with_capacity(10, sizeof *integers);`
 * 
 * @param capacity Number of items to allocate
 * @param stride The size of the items to go in the vector
 * @return A new vector of specified capacity
 */
vec_t vec_with_capacity(size_t capacity, size_t stride);

/**
 * @brief Delete a vector
 * 
 * @param The vector to be deleted
 */
void vec_del(vec_t vec);

/**
 * @brief Set contents of vector to zero, set len to max
 * 
 * @note Overwrites any values currently in vector
 * 
 * @param vec The vector to be zeroed 
 */
void vec_zero(vec_t vec);

/**
 * @brief Set contents of vector to zero, set len to max
 * 
 * @note Keeps items currently in buffer
 * 
 * @param vec The vector to be zeroed 
 */
void vec_zero_rest(vec_t vec);

/**
 * @brief Fill vector with specified value
 * 
 * @note Overwrites any values currently in vector
 * 
 * @param vec The vector to be filled
 * @param item The item to fill vector with
 */
void vec_fill(vec_t vec, void* item);

/**
 * @brief Fill vector with specified value
 * 
 * @note Keeps items currently in vector, fills in the rest
 * 
 * @param vec The vector to be filled
 * @param item The item to fill vector with
 */
void vec_fill_rest(vec_t vec, void* item);

/**
 * @brief Get the capacity of the vector
 * 
 * @note Capacity is how many items the vector is able to store 
 * without re-allocating, the length is zero until values are pushed 
 * into the vector 
 * 
 * @param vec The vector to get the capacity of
 * @return The capacity
 */
size_t vec_capacity(vec_t vec);

/**
 * @brief Get the length of the vector
 * 
 * @param vec The vector to get the length of
 * @return The length
 */
size_t vec_len(vec_t vec);

/**
 * @brief Set the length of the vector, useful if items are added manually
 * 
 * @param vec The vector whos length to set
 * @param new_len The new length of the vector
 */
void vec_set_len(vec_t vec, size_t new_len);

/**
 * @brief Grow the size of the vector 
 * 
 * @param vec Pointer to the vector to be grown
 */
void vec_grow_size(vec_t* vec);

/**
 * @brief Try to grow the size of the vector 
 * 
 * @param vec Pointer to the vector to be grown
 * @return false if vector could not be grown (out of memory)
 */
bool try_vec_grow_size(vec_t* vec);

/**
 * @brief Push an item onto the vector, grow vector if too small
 * 
 * @param vec The vector
 * @param item The item to be pushed onto the vector
 */
void vec_push(vec_t* vec, void* item);

/**
 * @brief Try to push an item onto the vector, grow vector if too small
 * 
 * @param vec The vector
 * @param item The item to be pushed onto the vector
 * @return false if the item could not be pushed (out of memory)
 */
bool try_vec_push(vec_t* vec, void* item);

/**
 * @brief Push an item onto the vector, panic if vector is too small
 * 
 * @param vec The vector
 * @param item The item to be pushed onto the vector
 */
void vec_push_to_capacity(vec_t vec, void* item);

/**
 * @brief Try to push an item onto the vector, fail if vector is too small
 * 
 * @param vec The vector
 * @param item The item to be pushed onto the vector
 * @return false if the vector is too small
 */
bool try_vec_push_to_capacity(vec_t vec, void* item);

/**
 * @brief Pop an item off of the vector, panic if empty
 * 
 * @param vec The vector to be popped
 * @param item The popped item will be copied here, pass NULL to discard item
 */
void vec_pop(vec_t vec, void* item);

/**
 * @brief Pop an item off of the vector, fail if empty
 * 
 * @param vec The vector to be popped
 * @param item The popped item will be copied here, pass NULL to discard item
 * @return false if pop failed
 */
bool try_vec_pop(vec_t vec, void* item);

/**
 * @brief Remove all items from vector 
 * @param vec Vector to be reset
 */
void vec_reset(vec_t vec);

#endif // VEC_C