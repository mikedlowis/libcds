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

void ht_free(ht_table* table)
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

int ht_put(ht_table* table, void* key, void* val)
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
    return 1;
}

void* ht_get(ht_table* table, char* key)
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

unsigned int ht_delete(ht_table* table, char* key)
{
    return 0;
}

unsigned int ht_resize(ht_table* table, unsigned int size)
{
    return 0;
}

