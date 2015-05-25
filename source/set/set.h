/**
  @file set.h
  @brief Implementation of a HashSet data structure.
*/
#ifndef SET_H
#define SET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rbt.h"

/** Function pointer that returns the 32-bit hash of the given object. */
typedef uint32_t (*hashfn_t)(void* obj);

/* Set data structure */
struct set_t;

/* Set stat structure type alias */
typedef struct set_t set_t;

/**
 * @brief Initializes a new set data structure.
 *
 * The initialized set will use the provided comparator and hash function for
 * lookups and retrievals.
 *
 * @param cmp The comparator used to compare the object types stored in the set.
 * @param hash_fn The function used to hash the objects in the set.
 *
 * @return the newly constructed set.
 */
set_t* set_new(cmp_t* cmp, hashfn_t hash_fn);

/**
 * @brief Determines if the value is a member of the set.
 *
 * @param set The set.
 * @param value The value to find.
 *
 * @return True if the value is a member, false otherwise.
 */
bool set_contains(set_t* set, void* value);

/**
 * @brief Returns the number of members in the set.
 *
 * @param set The set.
 *
 * @return The number of members in the set.
 */
size_t set_size(set_t* set);

/**
 * @brief Insert a value into the set.
 *
 * @param set The set.
 * @param value The value to insert.
 */
void set_insert(set_t* set, void* value);

/**
 * @brief Delete a value from the set.
 *
 * @param set The set.
 * @param value The value to delete.
 */
void set_delete(set_t* set, void* value);

#ifdef __cplusplus
}
#endif

#endif /* SET_H */
