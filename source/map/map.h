/**
  @file map.h
  @brief Implementation of a HashMap data structure.
*/
#ifndef MAP_H
#define MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rbt.h"

/** Function pointer that returns the 32-bit hash of the given object. */
typedef uint32_t (*map_hashfn_t)(void* obj);

/* map data structure */
struct map_t;

/* map stat structure type alias */
typedef struct map_t map_t;

/**
 * @brief Create a new map with the provided comparator and hash function.
 *
 * @param cmp User-provided comparator.
 * @param hash_fn User provided hash function.
 *
 * @return The new map.
 */
map_t* map_new(cmp_t* cmp, map_hashfn_t hash_fn);

/**
 * @brief Determines whether the map contains the given key or not.
 *
 * @param map The map to search.
 * @param key The key to search for.
 *
 * @return True if the map has the key, false otherwise.
 */
bool map_has_key(map_t* map, void* key);

/**
 * @brief Returns the number of key/value pairs in the map.
 *
 * @param map The map.
 *
 * @return The number of keys.
 */
size_t map_size(map_t* map);

/**
 * @brief Lookup a value by key.
 *
 * @param map The map.
 * @param key The key to lookup.
 *
 * @return The value associated with the key or null if no association exists.
 */
void* map_lookup(map_t* map, void* key);

/**
 * @brief Associate the key with the given value in map.
 *
 * @param map The map.
 * @param key The key.
 * @param value The value.
 */
void map_insert(map_t* map, void* key, void* value);

/**
 * @brief Delete the given key/value association from the map.
 *
 * @param map The map.
 * @param key The key of the association to delete.
 */
void map_delete(map_t* map, void* key);

#ifdef __cplusplus
}
#endif

#endif /* MAP_H */
