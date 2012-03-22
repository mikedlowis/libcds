/******************************************************************************
 * Copyright (c) 2012, Michael D. Lowis
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
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
