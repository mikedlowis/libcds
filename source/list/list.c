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
    return list_index_of(list, NULL);
}

bool list_empty(list_t* list)
{
    return NULL == list->head;
}

list_node_t* list_prev(list_t* list, list_node_t* node){
    (void)list;
    return (node ? node->prev : NULL);
}

list_node_t* list_at(list_t* list, size_t index)
{
    list_node_t* node = list->head;
    size_t cur_index = 0;
    while( NULL != node && cur_index != index)
    {
        node = node->next;
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
    if(node)
    {
        mem_retain(node);
        list_delete_node(list, node);
    }
    return node;
}

list_node_t* list_pop_back( list_t* list )
{
    list_node_t* node = list->tail;
    if(node)
    {
        mem_retain(node);
        list_delete_node(list, node);
    }
    return node;
}

list_node_t* list_insert( list_t* list, size_t index, void* contents)
{
    list_node_t* new_node = NULL;
    list_node_t* prev = (index > 0 ? list_at(list, index-1) : NULL);
    if(prev || index == 0)
        new_node = list_insert_after(list, prev, contents);
    else
        mem_release(contents);
    return new_node;
}

list_node_t* list_insert_after( list_t* list, list_node_t* node, void* contents)
{
    list_node_t* new_node = list_new_node(contents);
    list_node_t* next = (node ? node->next : list->head);
    new_node->prev = node;
    new_node->next = next;
    //node's next ptr or list's head
    if(node)
        node->next = new_node;
    else
        list->head = new_node;
    //next's prev ptr or list's tail
    if(next)
        next->prev = new_node;
    else
        list->tail = new_node;
    return new_node;
}

void list_delete( list_t* list, size_t index)
{
    list_delete_node(list, list_at(list, index));
}

void list_delete_node(list_t* list, list_node_t* node)
{
    if(NULL != list && NULL != node)
    {
        if(NULL != node->prev)
            node->prev->next = node->next;
        else
            list->head = node->next;
        if(NULL != node->next)
            node->next->prev = node->prev;
        else
            list->tail = node->prev;
        node->next = NULL;
        node->prev = NULL;
        mem_release(node);
    }
}

void list_clear(list_t* list)
{
    list_node_t* node = list->tail;
    while(NULL != node)
    {
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

