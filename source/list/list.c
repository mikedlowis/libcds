#include <stdlib.h>
#include "list.h"

list_t* list_new(void)
{
    list_t* list = (list_t*)malloc( sizeof( list_t ) );
    list->head = NULL;
    list->tail = NULL;
    return list;
}

list_node_t* list_new_node(void* contents)
{
    list_node_t* node = (list_node_t*)malloc( sizeof( list_node_t ) );
    node->contents = contents;
    node->next = NULL;
    return node;
}

void list_free(list_t* list, bool free_contents)
{
    list_node_t* node = list->head;
    while( NULL != node )
    {
        list_node_t* next = node->next;
        list_free_node( node, free_contents );
        node = next;
    }
    free( list );
}

void list_free_node(list_node_t* node, bool free_contents)
{
    if( free_contents )
    {
        free( node->contents );
    }
    free( node );
}

list_node_t* list_front( list_t* list )
{
    return list->head;
}

list_node_t* list_back( list_t* list )
{
    return list->tail;
}

size_t list_size(list_t* list)
{
    size_t length = 0;
    list_node_t* node = list->head;
    while( NULL != node )
    {
        node = node->next;
        length++;
    }
    return length;
}

bool list_empty(list_t* list)
{
    return ((NULL == list->head) && (NULL == list->tail));
}


list_node_t* list_at(list_t* list, size_t index)
{
    list_node_t* node = NULL;
    size_t cur_index = 0;
    list_node_t* cur_node = list->head;
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
    return node;
}

list_node_t* list_push_front( list_t* list, void* contents )
{
    list_node_t* node = list_new_node( contents );
    node->next = list->head;
    list->head = node;
    if( NULL == list->tail )
    {
        list->tail = node;
    }
    return node;
}

list_node_t* list_push_back( list_t* list, void* contents )
{
    list_node_t* node = list_new_node( contents );
    node->next = NULL;
    if( NULL == list->tail )
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }
    return node;
}

list_node_t* list_pop_front( list_t* list )
{
    list_node_t* node = NULL;
    if( NULL != list->head )
    {
        node = list->head;
        list->head = node->next;
        if( node == list->tail )
        {
            list->tail = NULL;
        }
    }
    return node;
}

list_node_t* list_pop_back( list_t* list )
{
    list_node_t* node = NULL;
    if ( list->head == list->tail )
    {
        node = list->head;
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        list_node_t* next_tail = list->head;
        while( next_tail->next != list->tail )
        {
            next_tail = next_tail->next;
        }
        node = next_tail->next;
        next_tail->next = NULL;
        list->tail = next_tail;
    }
    return node;
}

list_node_t* list_insert( list_t* list, size_t index, void* contents)
{
    list_node_t* new_node = NULL;
    if( 0 == index )
    {
        new_node = list_push_front( list, contents );
    }
    else
    {
        list_node_t* prev_node = list_at( list, index - 1 );
        if( NULL != prev_node )
        {
            list_node_t* next_node = prev_node->next;
            new_node = list_new_node( contents );
            new_node->next = next_node;
            prev_node->next = new_node;
            if( NULL == next_node )
            {
                list->tail = new_node;
            }
        }
    }
    return new_node;
}

list_node_t* list_delete( list_t* list, size_t index, bool free_contents)
{
    list_node_t* node = NULL;

    if (0 == index)
    {
        node = list_pop_front(list);
        if (NULL != node)
        {
            list_free_node(node,free_contents);
            node = list_front(list);
        }
    }
    else
    {
        list_node_t* prev = list_at(list,index-1);
        node = (NULL == prev) ? NULL : prev->next;
        if (NULL != node)
        {
            prev->next = node->next;
            if (NULL == prev->next)
            {
                list->tail = prev;
            }
            list_free_node(node,free_contents);
            node = prev->next;
        }
    }

    return node;
}

list_t* list_clear(list_t* list, bool free_contents)
{
    list_node_t* node = list->head;
    while(NULL != node)
    {
        list_node_t* next = node->next;
        list_free_node(node,free_contents);
        node = next;
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

