#include "sll.h"
#include <stdlib.h>

sll_t* sll_new(void)
{
    sll_t* list = (sll_t*)malloc( sizeof( sll_t ) );
    list->head = NULL;
    list->tail = NULL;
    return list;
}

sll_node_t* sll_new_node(void* contents)
{
    sll_node_t* node = (sll_node_t*)malloc( sizeof( sll_node_t ) );
    node->contents = contents;
    node->next = NULL;
    return node;
}

void sll_free(sll_t* list, int free_contents)
{
    if( NULL != list )
    {
        sll_node_t* node = list->head;
        while( NULL != node )
        {
            sll_node_t* next = node->next;
            sll_free_node( node, free_contents );
            node = next;
        }
        free( list );
    }
}

void sll_free_node(sll_node_t* node, int free_contents)
{
    if( NULL != node )
    {
        if( 1 == free_contents )
        {
            free( node->contents );
        }
        free( node );
    }
}

unsigned int sll_length(sll_t* list)
{
    unsigned int length = 0;
    if( NULL != list)
    {
        sll_node_t* node = list->head;
        while( NULL != node )
        {
            node = node->next;
            length++;
        }
    }
    return length;
}

sll_node_t* sll_index(sll_t* list, unsigned int index)
{
    sll_node_t* node = NULL;
    if( NULL != list )
    {
        unsigned int cur_index = 0;
        sll_node_t* cur_node = list->head;
        while( NULL != cur_node )
        {
            if( cur_index == index )
            {
                node = cur_node;
                break;
            }
            cur_node = cur_node->next;
            cur_index++;
        }
    }
    return node;
}

sll_node_t* sll_push_front( sll_t* list, void* contents )
{
    sll_node_t* node = NULL;
    if( NULL != list )
    {
        node = sll_new_node( contents );
        node->next = list->head;
        if( NULL == list->tail )
        {
            list->tail = node;
        }
    }
    return node;
}

sll_node_t* sll_push_back( sll_t* list, void* contents )
{
    sll_node_t* node = NULL;
    if( NULL != list )
    {
        node = sll_new_node( contents );
        node->next = NULL;
        if( NULL == list->tail )
        {
            list->head = node;
            list->tail = node;
        }
        else
        {
            list->tail->next = node;
        }
    }
    return node;
}

sll_node_t* sll_pop_front( sll_t* list, int free_contents )
{
    return 0;
}

sll_node_t* sll_pop_back( sll_t* list, int free_contents )
{
    return 0;
}

sll_node_t* sll_insert( sll_t* list, unsigned int index, void* contents)
{
    return 0;
}

sll_node_t* sll_delete( sll_t* list, unsigned int index, int free_contents)
{
    return 0;
}

