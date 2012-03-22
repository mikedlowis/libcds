/******************************************************************************
 *  Copyright (C) 2011  Michael D. Lowis
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

