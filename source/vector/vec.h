/**
    @file vec.h
    @brief TODO: Describe this file
    $Revision$
    $HeadURL$
*/
#ifndef VEC_H
#define VEC_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

/** A vector implementation */
typedef struct {
    size_t size;       /*< The number of elements currently in the array */
    size_t capacity;   /*< The size of the internal array */
    void** p_buffer;   /*< Pointer to the array */
} vec_t;

#ifdef __cplusplus
extern "C" {
#endif

/** The default capacity of the vector if no initializing elements have been
 *  provided. */
#ifndef DEFAULT_VEC_CAPACITY
#define DEFAULT_VEC_CAPACITY (size_t)8
#endif

/**
 * @brief Creates a new vector initialized with the given elements.
 *
 * @param num_elements The number of elements to be put into the vector.
 * @param ... The list of elements (length must be equal to num_elements).
 *
 * @return Pointer to newly created vector.
 */
vec_t* vec_new(size_t num_elements, ...);

/**
 * @brief Returns the number of items in the vector.
 *
 * @param p_vec Pointer to the vector.
 *
 * @return The number of items in the vector.
 */
size_t vec_size(vec_t* p_vec);

/**
 * @brief Returns the maximum number of items that could be contained in a vector.
 *
 * @return The maximum size of a vector.
 */
size_t vec_max_size(void);

/**
 * @brief Returns whether the vector is empty (size == 0) or not.
 *
 * @param p_vec Pointer to the vector.
 *
 * @return Whether the vector is empty.
 */
bool vec_empty(vec_t* p_vec);

/**
 * @brief Resizes the vector to contain the specified number of elements.
 *
 * @param p_vec Pointer to the vector.
 * @param size The target size of the vector.
 * @param data The value of any newly created elements.
 */
void vec_resize(vec_t* p_vec, size_t size, void* data);

/**
 * @brief Returns the next power of two that is not less than the desired size.
 *
 * @param req_size The desired size of the vector.
 *
 * @return The necessary capacity.
 */
size_t vec_next_capacity(size_t req_size);

/**
 * @brief Shrinks the vector's capacity to equal it's size.
 *
 * @param p_vec Pointer to the vector.
 */
void vec_shrink_to_fit(vec_t* p_vec);

/**
 * @brief Returns the size of the internal array that is currently in use.
 *
 * @param p_vec Pointer to the vector.
 *
 * @return The size of the internal array.
 */
size_t vec_capacity(vec_t* p_vec);

/**
 * @brief Sets the minimum storage capacity of the vector to the given size.
 *
 * @param p_vec Pointer to the vector.
 * @param size The size to reserve.
 */
void vec_reserve(vec_t* p_vec, size_t size);

/**
 * @brief Returns the item at the specified index.
 *
 * @param p_vec Pointer to the vector.
 * @param index The index of the item to retrieve.
 *
 * @return The retrieved item.
 */
void* vec_at(vec_t* p_vec, size_t index);

/**
 * @brief Sets the value of the element at the given index.
 *
 * @param p_vec Pointer to the vector.
 * @param index The index of the element to set.
 * @param data The new data for the indexed element.
 */
bool vec_set(vec_t* p_vec, size_t index, void* data);

/**
 * @brief Inserts the provided elements at the given index.
 *
 * @param p_vec Pointer to the vector.
 * @param index Index at which the elements should be inserted.
 * @param num_elements The number of elements to insert.
 * @param ... The elements to insert.
 */
bool vec_insert(vec_t* p_vec, size_t index, size_t num_elements, ...);

/**
 * @brief Erases elements from the vector that fall into the given range.
 *
 * @param p_vec Pointer to the vector.
 * @param start_idx The start of the range.
 * @param end_idx The end of the range.
 *
 * @return Whether the operation was successful.
 */
bool vec_erase(vec_t* p_vec, size_t start_idx, size_t end_idx);

/**
 * @brief Pushes the provided element on to the back of the vector.
 *
 * @param p_vec Pointer to the vector.
 * @param data The data to push.
 */
void vec_push_back(vec_t* p_vec, void* data);

/**
 * @brief Erases and returns the last element in the vector.
 *
 * @param p_vec Pointer to the vector.
 *
 * @return The element that was removed.
 */
void* vec_pop_back(vec_t* p_vec);

/**
 * @brief Erases all elements in the vector.
 *
 * @param p_vec Pointer to the vector.
 */
void vec_clear(vec_t* p_vec);

#ifdef __cplusplus
}
#endif

#endif /* VEC_H */
