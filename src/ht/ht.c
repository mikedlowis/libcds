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
#include "ht.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

unsigned int ht_hash_string(void* key)
{
    char* key_str = (char*)key;
    unsigned int hash = 0;
    int i = 0;
    for (i = 0; key_str[i] != '\0'; i++)
    {
        hash += key_str[i];
    }
    return hash;
}

ht_table* ht_new(unsigned int size, ht_hash_func fn)
{
    unsigned int table_size = size * sizeof(ht_node*);
    ht_table* table = (ht_table*) malloc( sizeof(ht_table) );
    table->size = size;
    table->table = (ht_node**) malloc( table_size );
    table->hash_func = (fn != NULL) ? fn : ht_hash_string;
    memset(table->table, 0, table_size);
    return table;
}

void ht_free(ht_table* table, int free_key, int free_value)
{
    int i = 0;
    for (i = 0; i < table->size; i++)
    {
        ht_node* cur = table->table[i];
        while (cur != NULL)
        {
            printf("Index: %d\tKey: %s\tVal: %#x\tNext: %#x\n", i, cur->key, (int)cur->val, (int)cur->next);
            ht_node* next = cur->next;
            free( cur->key );
            free( cur->val );
            free( cur );
            cur = next;
        }
    }
}

void ht_put(ht_table* table, void* key, void* val)
{
    unsigned int index = table->hash_func( key ) % table->size;
    ht_node* cur = table->table[index];
    ht_node* last = cur;

    while (cur != NULL)
    {
        if ( !strcmp( key, cur->key ) )
        {
            cur->val = val;
            break;
        }
        last = cur;
        cur = cur->next;
    }

    if (cur == NULL)
    {
        ht_node* node = (ht_node*) malloc( sizeof(ht_node) );
        node->key = (char*) strdup( key );
        node->val = val;
        node->next = NULL;

        if (last != NULL)
        {
            last->next = node;
        }
        else
        {
            table->table[ index ] = node;
        }
    }
}

void* ht_get(ht_table* table, void* key)
{
    void* ret = NULL;
    unsigned int index= table->hash_func( key ) % table->size;
    ht_node* node = table->table[ index ];
    while ( node != NULL )
    {
        if ( !strcmp( key, node->key ) )
        {
            ret = node->val;
            break;
        }
        node = node->next;
    }
    return ret;
}

void ht_delete(ht_table* table, void* key, int free_key, int free_value)
{
    return 0;
}

ht_table* ht_resize(ht_table* table, unsigned int size)
{
    return 0;
}

