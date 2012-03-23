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
#ifndef HT_H
#define HT_H

//! Hash function for hashing keys in a hash table
typedef unsigned int (*ht_hash_func) (void*);

//! A node in a hash table.
typedef struct ht_node
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
 * This function takes a pointer to a string and returns a hash value based on
 * the contents of the string.
 *
 * @param key Pointer to the string to hash.
 *
 * @return The hashed value of the key.
 **/
unsigned int ht_hash_string(void* key);

/**
 * @brief Creates a new hash table
 *
 * This fucntion creates a new empty hash table with an internal lookup table
 * of the given size and the desired hash function. The hash function will be
 * used for insertion, deletion, and lookup of elements within the table. If
 * the hash function pointer is null then ht_hash_string is used.
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
 * This function frees all memory allocated for the given table. If free_key or
 * free_value are non-zero values then the key or value pointers are freed
 * respectively.
 *
 * @param table      The table to be freed.
 * @param free_key   Determines whether the key pointers will be freed.
 * @param free_value Determines whether the value pointers will be freed.
 **/
void ht_free(ht_table* table, int free_key, int free_value);

/**
 * @brief Inserts a key/value pair into the provided table.
 *
 * This function inserts a new entry into the provided table containing the
 * provided key and value pointers. The entry is placed in the table by hashing
 * the key with the provided table's hash function. If an entry with an
 * identical key exists, then the value pointer for that entry is changed to
 * the provided value pointer. If free_value is a non-zero value then the old
 * value pointer is also freed.
 *
 * @param table      The table to be freed.
 * @param key        The key for the associated value.
 * @param val        The value to be associated with the key.
 * @param free_value Determines whether or not to free the old value pointer.
 **/
void ht_insert(ht_table* table, void* key, void* val);

/**
 * @brief Retrieves a value from the provided table.
 *
 * This function looks up an entry in the table by hashing the key with the
 * table's hash function. It then returns the pointer to the value of the found
 * entry or a null pointer if no entry was found.
 *
 * @param table The table in which to find the associated value.
 * @param key   The key to lookup.
 *
 * @return A pointer to the value associated with the provided key.
 **/
void* ht_find(ht_table* table, void* key);

/**
 * @brief Deletes a key/value pair from the provided hash table.
 *
 * This function looks up an entry in the table by hashing the key with the
 * table's hash function. If an entry is found then the memory allocated for
 * the entry is freed. If free_key or free_value are non-zero values then the
 * key or value pointers are freed respectively.
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
 * This function allocates a new internal lookup table of the given size to
 * replace the internal table for the provided hash table. After the new talbe
 * is created, all entries from the old table are rehahsed and inserted into
 * the new lookup table. The new lookup table then replaces the old lookup
 * table and the old lookup table is freed.
 *
 * @param table The table to be resized.
 * @param size  The new size for the table.
 *
 * @return A pointer to the resized table.
 **/
ht_table* ht_resize(ht_table* table, unsigned int size);

#endif
