/**
  @file mem.h
  @brief TODO: Describe this file
  $Revision$
  $HeadURL$
  */
#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/** A function pointer for object destructors */
typedef void (*destructor_t)(void* p_val);

/**
 * @brief Allocates a new reference counted object of the given size which will
 *        be destructed with the given function before it's memory is reclaimed.
 *
 * @param size The number of bytes to allocate for this object.
 * @param p_destruct_fn The function to call when reclaiming this object.
 *
 * @return Pointer to the newly allocated object
 */
void* mem_allocate(size_t size, destructor_t p_destruct_fn);

/**
 * @brief Increments the reference count for the given object.
 *
 * @param p_obj The object to be retained.
 */
void mem_retain(void* p_obj);

/**
 * @brief Decrements the reference count for a given object.
 *
 * @param p_obj The object to be released.
 */
void mem_release(void* p_obj);

/**
 * @brief Schedules an object to be released at a later time when more convenient.
 *
 * @param p_obj The object to be released.
 */
void mem_autorelease(void* p_obj);

/**
 * @brief Release all objects scheduled to be released reclaiming their memory
 *        if necessary.
 */
void mem_releaseall(void);

/**
 * @brief Create a reference counted box holding the given value so that it can
 *        be placed in a container.
 *
 * @param val The value to be boxed.
 *
 * @return The pointer to the newly allocated box.
 */
void* mem_box(intptr_t val);

/**
 * @brief Release a reference counted box and return it's contained value.
 *
 * @return The boxed value.
 */
intptr_t mem_unbox(void* p_box);

#ifdef __cplusplus
}
#endif

#endif /* MEM_H */