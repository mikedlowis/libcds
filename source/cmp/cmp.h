/**
  @file cmp.h
  @brief TODO: Describe this file
  */
#ifndef CMP_H
#define CMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rt.h"

/** Function pointer representing a comparison function with an additional
 * environment pointer */
typedef int (*cmpfn_t)(void* env, void* obja, void* objb);

/** Comparator object */
typedef struct {
    void* env;  /**< The environment context associated with this comparator */
    cmpfn_t fn; /**< The comparison function for this comparator */
} cmp_t;

/**
 * @brief Constructs a new comparator object.
 *
 * @param env The environment context associated with the comparator
 * @param fn The comparison function associated with the comparator
 *
 * @return The newly constructed comparator.
 */
cmp_t* cmp_new(void* env, cmpfn_t fn);

/**
 * @brief Compares two objects using the comparator object.
 *
 * @param cmp The comparator to use.
 * @param obja First object to compare.
 * @param objb Second object to compare.
 *
 * @return 0  if objects are equal
 *         -1 if obja is less than objb
 *         1  if obja is greater than objb
 */
int cmp_compare(cmp_t* cmp, void* obja, void* objb);

#ifdef __cplusplus
}
#endif

#endif /* CMP_H */
