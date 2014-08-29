/**
  @file vec.c
  @brief See header for details
  $Revision$
  $HeadURL$
*/
#include "vec.h"

static void vec_free(void* p_vec);

static void vec_free_range(void** p_buffer, size_t start_idx, size_t end_idx);

vec_t* vec_new(size_t num_elements, ...)
{
    vec_t* p_vec;
    va_list elements;
    size_t index;

    /* Allocate and construct the vector object */
    p_vec = (vec_t*)mem_allocate(sizeof(vec_t), vec_free);
    assert(p_vec != NULL);
    p_vec->size = num_elements;
    p_vec->capacity = (0 == num_elements) ? DEFAULT_VEC_CAPACITY : num_elements;
    p_vec->p_buffer = (void**)calloc( sizeof(void*), p_vec->capacity );
    assert(p_vec->p_buffer != NULL);

    /* Populate the array with the elements list */
    va_start(elements, num_elements);
    for (index = 0; index < num_elements; index++)
    {
        p_vec->p_buffer[index] = va_arg(elements,void*);
    }
    va_end(elements);

    return p_vec;
}

size_t vec_size(vec_t* p_vec)
{
    assert(NULL != p_vec);
    return p_vec->size;
}

size_t vec_max_size(void)
{
    return (size_t)-1;
}

bool vec_empty(vec_t* p_vec)
{
    assert(NULL != p_vec);
    return (0 == vec_size(p_vec));
}

void vec_resize(vec_t* p_vec, size_t size, void* data)
{
    assert(NULL != p_vec);
    if (size > p_vec->size)
    {
        vec_reserve(p_vec,vec_next_capacity(size+1));
        for (; p_vec->size < size; p_vec->size++)
        {
            p_vec->p_buffer[ p_vec->size ] = data;
            if((NULL != data) && ((size - p_vec->size) > 1))
                mem_retain(data);
        }
    }
    else if (size < p_vec->size)
    {
        vec_free_range(p_vec->p_buffer, size, p_vec->size);
        p_vec->size = size;
    }
}

size_t vec_next_capacity(size_t req_size)
{
    size_t next_power = req_size;
    size_t num_bits = sizeof(size_t) * 8;
    size_t bit_n;

    /* Find the next highest power of 2 */
    next_power--;
    for (bit_n = 1; bit_n < num_bits; bit_n = bit_n << 1)
    {
        next_power = next_power | (next_power >> bit_n);
    }
    next_power++;

    return next_power;
}

void vec_shrink_to_fit(vec_t* p_vec)
{
    assert(NULL != p_vec);
    p_vec->p_buffer = realloc( p_vec->p_buffer, sizeof(void*) * p_vec->size );
    assert(p_vec->p_buffer != NULL);
    p_vec->capacity = p_vec->size;
}

size_t vec_capacity(vec_t* p_vec)
{
    return p_vec->capacity;
}

void vec_reserve(vec_t* p_vec, size_t size)
{
    assert(p_vec != NULL);
    p_vec->p_buffer = realloc( p_vec->p_buffer, sizeof(void*) * size );
    assert(p_vec->p_buffer != NULL);
    p_vec->capacity = size;
}

void* vec_at(vec_t* p_vec, size_t index)
{
    void* p_ret = NULL;
    if (index < p_vec->size)
    {
        p_ret = p_vec->p_buffer[index];
    }
    return p_ret;
}

bool vec_set(vec_t* p_vec, size_t index, void* data)
{
    bool ret = false;
    if (index < p_vec->size)
    {
        p_vec->p_buffer[index] = data;
        ret = true;
    }
    return ret;
}

bool vec_insert(vec_t* p_vec, size_t index, size_t num_elements, ...)
{
    bool ret = false;
    va_list elements;
    size_t new_size;
    if ((index < p_vec->size) && (num_elements > 0))
    {
        /* Resize the vector to fit the new contents */
        vec_resize( p_vec, p_vec->size + num_elements, NULL );
        /* Move the displaced items to the end */
        memmove(&(p_vec->p_buffer[index + num_elements]),
                &(p_vec->p_buffer[index]),
                sizeof(void*) * (p_vec->size - index));
        /* insert the new items */
        va_start(elements, num_elements);
        new_size = index + num_elements;
        for (; index < new_size; index++)
        {
            p_vec->p_buffer[index] = va_arg(elements,void*);
        }
        va_end(elements);
        ret = true;
    }
    return ret;
}

bool vec_erase(vec_t* p_vec, size_t start_idx, size_t end_idx)
{
    bool ret = false;
    /* if the range is valid */
    if ((start_idx < p_vec->size) && (end_idx < p_vec->size) && (start_idx <= end_idx))
    {
        /* Free the range of data */
        vec_free_range(p_vec->p_buffer, start_idx, end_idx + 1);
        /* Compact the remaining data */
        memmove(&(p_vec->p_buffer[start_idx]), /* Destination is beginning of erased range */
                &(p_vec->p_buffer[end_idx+1]), /* Source is end of erased range */
                sizeof(void*) * (p_vec->size - end_idx - 1));
        /* Shrink the size */
        p_vec->size = p_vec->size - ((end_idx - start_idx) + 1);
        ret = true;
    }
    return ret;
}

void vec_push_back(vec_t* p_vec, void* data)
{
    vec_resize(p_vec, p_vec->size+1, data);
}

void* vec_pop_back(vec_t* p_vec)
{
    void* p_ret = NULL;
    if (p_vec->size > 0)
    {
        p_vec->size = p_vec->size - 1;
        p_ret = p_vec->p_buffer[p_vec->size];
    }
    return p_ret;
}

void vec_clear(vec_t* p_vec)
{
    vec_free_range(p_vec->p_buffer, 0, p_vec->size);
    p_vec->size = 0;
}

static void vec_free(void* p_vec)
{
    vec_t* p_vector = (vec_t*)p_vec;
    assert(NULL != p_vector);
    assert(NULL != p_vector->p_buffer);
    vec_clear(p_vector);
    free(p_vector->p_buffer);
    p_vector->p_buffer = NULL;
}

static void vec_free_range(void** p_buffer, size_t start_idx, size_t end_idx)
{
    size_t i;
    assert(NULL != p_buffer);
    for(i = start_idx; i < end_idx; i++)
    {
        if (NULL != p_buffer[i])
        {
            mem_release(p_buffer[i]);
            p_buffer[i] = NULL;
        }
    }
}

