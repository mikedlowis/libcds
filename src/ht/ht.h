/******************************************************************************
 *  Copyright (C) 2011 Michael D. Lowis
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
#ifndef HASHTABLE_H
#define HASHTABLE_H

//! Hash function for hashing keys in a hash table
typedef unsigned int (*ht_hash_func) (void*);

//! A node in a hash table.
typedef struct node
{
    //! Pointer to the key
    void* key;
    //! Pointer to the value
    void* val;
    //! Pointer to the next node in the collision chain
    struct node* next;
} ht_node;

//! A hash table
typedef struct
{
    //! Size of the internal table
    unsigned int size;
    //! Pointer to the internal hashing table
    ht_node** table;
    //! Function used for hashing elements
    ht_hash_func hash_func;
} ht_table;

/**
 * @brief Takes a string key value and returns it's hashed value.
 *
 * @param key    Pointer to the string to hash.
 *
 * @return The hashed value of the key.
 **/
unsigned int ht_hash_string(void* key);

/**
 * @brief Creates a new hash table of the given size using the provided hash function
 * or the built-in string hashing function otherwise.
 *
 * @param size The size of the table to use for storing data.
 * @param fn   The function to use for hasing keys.
 *
 * @return The newly created table.
 **/
ht_table* ht_new(unsigned int size, ht_hash_func fn);

/**
 * @brief Frees all memory used by the provided hash table.
 *
 * @param table      The table to be freed.
 * @param free_key   Determines whether the key pointers will be freed.
 * @param free_value Determines whether the value pointers will be freed.
 **/
void ht_free(ht_table* table, int free_key, int free_value);

/**
 * @brief Inserts a key/value pair into the provided table.
 *
 * @param table The table to be freed.
 * @param key   The key for the associated value.
 * @param val   The value to be associated with the key.
 **/
void ht_put(ht_table* table, void* key, void* val);

/**
 * @brief Retrieves a value from the provided table.
 *
 * @param table The table in which to find the associated value.
 * @param key   The key to lookup.
 *
 * @return A pointer to the value associated with the provided key.
 **/
void* ht_get(ht_table* table, void* key);

/**
 * @brief Deletes a key/value pair from the provided hash table.
 *
 * @param table      The table from which the key/value pait will be deleted.
 * @param key        The key for the key/value pair to be deleted.
 * @param free_key   Determines whether the key pointer will be freed.
 * @param free_value Determines whether the value pointer will be freed.
 **/
void ht_delete(ht_table* table, void* key, int free_key, int free_value);

/**
 * @brief Resizes the underlying table used for storing key/value pairs.
 *
 * @param table The table to be resized.
 * @param size  The new size for the table.
 *
 * @return A pointer to the resized table.
 **/
ht_table* ht_resize(ht_table* table, unsigned int size);

#endif
