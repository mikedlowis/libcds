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
#include "sll.h"
#include <stdlib.h>

/******************************************************************************
 * Public Functions
 ******************************************************************************/
sll_node* sll_new( void* contents )
{
    sll_node* list = (sll_node*)malloc( sizeof(sll_node) );
    list->contents = contents;
    list->next = NULL;
    return list;
}

sll_node* sll_last( sll_node* list )
{
    sll_node* node = list;
    while((node != NULL) && (node->next != NULL))
    {
        node = node->next;
    }
    return node;
}

sll_node* sll_get( sll_node* list, int index )
{
    int current = 0;
    sll_node* node = list;
    sll_node* indexed_node = NULL;
    while ((node != NULL))
    {
        if ( current == index )
        {
            indexed_node = node;
            break;
        }
        node = node->next;
        current++;
    }
    return indexed_node;
}

sll_node* sll_add( sll_node* list, void* contents )
{
    sll_node* node = sll_last( list );
    node->next = sll_new( contents );
}

sll_node* sll_insert( sll_node* list, int index, void* contents )
{
    int req_index = ((index-1) < 0) ? 0 : index-1;
    sll_node* node = sll_get( list, req_index );
    if(node != NULL)
    {
        sll_node* next_next = node->next;
        node->next = sll_new( contents );
        node->next->next = next_next;
        node = node->next;
    }
    return node;
}

sll_node* sll_delete( sll_node* list, int index, int free_contents)
{
    sll_node* node = sll_get( list, (index-1));
    if((node != NULL) && (node->next != NULL))
    {
        sll_node* node_to_delete = node->next;
        node->next = node_to_delete->next;
        if (free_contents)
        {
            free(node_to_delete->contents);
        }
        free(node_to_delete);
        node = node->next;
    }
    return node;
}

void sll_free( sll_node* list, int free_contents)
{
    sll_node* node = list;
    while( node != NULL )
    {
        sll_node* next = node->next;
        if (free_contents)
            {
            free(node->contents);
            }
        free(node);
        node = next;
    }
}

unsigned int sll_length(sll_node* list)
{
    unsigned int length = 0;
    sll_node* item = list;
    for ( item = list; item != NULL; item = item->next )
    {
        length++;
    }
    return length;
}

