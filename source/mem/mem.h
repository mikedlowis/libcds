/**
  @file mem.h
  @brief Implements reference counting routines for C.
  */
#ifndef MEM_H
#define MEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rt.h"

/** A function pointer for object destructors */
typedef void (*destructor_t)(void* p_val);

/** Unless otherwise specified, no leak detection will occur */
#ifndef LEAK_DETECT_LEVEL
#define LEAK_DETECT_LEVEL 0
#endif

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
 * @brief Returns the reference count for the given object.
 *
 * @param p_obj The object whose reference count should be returned.
 *
 * @return Number of references.
 */
int mem_refcount(void* p_obj);

/**
 * @brief Increments the reference count for the given object.
 *
 * @param p_obj The object to be retained.
 */
void* mem_retain(void* p_obj);

/**
 * @brief Decrements the reference count for a given object.
 *
 * @param p_obj The object to be released.
 */
void mem_release(void* p_obj);

/**
 * @brief Replaces the object reference in the given location with the new
 *        object releasing the old one.
 *
 * @param loc Pointer to the location where the reference is kept.
 * @param obj The new object the location will point to.
 */
void mem_swap(void** loc, void* obj);

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
