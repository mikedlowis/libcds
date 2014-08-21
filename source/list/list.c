#include <stdlib.h>
#include "list.h"
#include "mem.h"

static void list_free(void* p_list);

static void list_node_free(void* p_node);

list_t* list_new(void)
{
    list_t* list = (list_t*)mem_allocate(sizeof(list_t), &list_free);
    list->head = NULL;
    list->tail = NULL;
    return list;
}

list_node_t* list_new_node(void* contents)
{
    list_node_t* node = (list_node_t*)mem_allocate(sizeof(list_node_t), &list_node_free);
    node->contents = contents;
    node->prev = NULL;
    node->next = NULL;
    return node;
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

list_node_t* list_prev(list_t* list, list_node_t* node){
    (void)list;
    return (node ? node->prev : NULL);
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

int list_index_of(list_t* list, list_node_t* node)
{
    int i = 0;
    list_node_t* edon = list->head;
    while( NULL != edon && edon != node)
    {
        edon = edon->next;
        i++;
    }
    return (node == edon) ? i : -1;
}

list_node_t* list_push_front( list_t* list, void* contents )
{
    return list_insert_after(list, NULL, contents);
}

list_node_t* list_push_back( list_t* list, void* contents )
{
    return list_insert_after(list, list->tail, contents);
}

list_node_t* list_pop_front( list_t* list )
{
    list_node_t* node = list->head;
    if(node){
        mem_retain(node);
        list_delete_node(list, node);
    }
    return node;
}

list_node_t* list_pop_back( list_t* list )
{
    list_node_t* node = list->tail;
    if(node){
        mem_retain(node);
        list_delete_node(list, node);
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
            new_node = list_insert_after(list, prev_node, contents);
        }
        else
        {
            mem_release(contents);
        }
    }
    return new_node;
}

list_node_t* list_insert_after( list_t* list, list_node_t* node, void* contents)
{
    list_node_t* new_node = list_new_node(contents);
    if(NULL != node)
    {
        new_node->prev = node;
        new_node->next = node->next;
        if(node->next) node->next->prev = new_node;
        node->next = new_node;
    }
    else
    {
        new_node->next = list->head;
        if(list->head) list->head->prev = new_node;
        list->head = new_node;
    }
    if (node == list->tail)
    {
        list->tail = new_node;
    }
    return new_node;
}

list_node_t* list_delete( list_t* list, size_t index)
{
    list_node_t* node = list_at(list, index);
    if(node){
        list_node_t* next = node->next;
        list_delete_node(list, node);
        return next;
    }
    else{
        return NULL;
    }
}

void list_delete_node(list_t* list, list_node_t* node)
{
    if(NULL != list && NULL != node)
    {
        int idx = list_index_of(list, node); //TODO: why the fuck is this necessary?
        if(idx > -1){
            if(NULL != node->prev) node->prev->next = node->next;
            else list->head = node->next;
            if(NULL != node->next) node->next->prev = node->prev;
            else list->tail = node->prev;
            node->next = NULL;
            node->prev = NULL;
            mem_release(node);
        }
    }
}

void list_clear(list_t* list)
{
    list_node_t* node = list->tail;
    while(NULL != node){
        list_node_t* p = node->prev;
        node->prev = NULL;
        node->next = NULL;
        mem_release((void*) node);
        node = p;
    }
    list->head = NULL;
    list->tail = NULL;
}

static void list_free(void* p_list)
{
    if (NULL != ((list_t*)p_list)->head)
        mem_release(((list_t*)p_list)->head);
}

static void list_node_free(void* p_node)
{
    if (NULL != ((list_node_t*)p_node)->contents)
        mem_release(((list_node_t*)p_node)->contents);
    if (NULL != ((list_node_t*)p_node)->next)
        mem_release(((list_node_t*)p_node)->next);
}

