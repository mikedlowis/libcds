/**
  @file list.c
  @brief See header for details
  $Revision$
  $HeadURL$
  */
#include "list.h"

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
    assert(NULL != list);
    return list->head;
}

list_node_t* list_back( list_t* list )
{
    assert(NULL != list);
    return list->tail;
}

size_t list_size(list_t* list)
{
    assert(NULL != list);
    return list_index_of(list, NULL);
}

bool list_empty(list_t* list)
{
    assert(NULL != list);
    return NULL == list->head;
}

list_node_t* list_prev(list_t* list, list_node_t* node){
    (void)list;
    return (node ? node->prev : NULL);
}

list_node_t* list_at(list_t* list, size_t index)
{
    list_node_t* node;
    size_t cur_index = 0;
    assert(NULL != list);
    node = list->head;
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
    list_node_t* edon;
    assert(NULL != list);
    edon = list->head;
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
    list_node_t* node;
    assert(NULL != list);
    node = list->head;
    if(node)
    {
        mem_retain(node);
        list_delete_node(list, node);
    }
    return node;
}

list_node_t* list_pop_back( list_t* list )
{
    list_node_t* node;
    assert(NULL != list);
    node = list->tail;
    if(node)
    {
        mem_retain(node);
        list_delete_node(list, node);
    }
    return node;
}

list_node_t* list_insert( list_t* list, size_t index, void* contents)
{
    list_node_t *prev, *new_node = NULL;
    assert(NULL != list);
    prev = (index > 0 ? list_at(list, index-1) : NULL);
    if(prev || index == 0)
        new_node = list_insert_after(list, prev, contents);
    else
        mem_release(contents);
    return new_node;
}

list_node_t* list_insert_after( list_t* list, list_node_t* node, void* contents)
{
    list_node_t *next, *new_node = list_new_node(contents);
    assert(NULL != list);
    assert(NULL != new_node);
    next = (node ? node->next : list->head);
    new_node->prev = node;
    new_node->next = next;
    *(node ? &(node->next) : &(list->head)) = new_node;
    *(next ? &(next->prev) : &(list->tail)) = new_node;
    return new_node;
}

void list_delete( list_t* list, size_t index)
{
    assert(NULL != list);
    list_delete_node(list, list_at(list, index));
}

void list_delete_node(list_t* list, list_node_t* node)
{
    assert(NULL != list);
    assert(NULL != node);
    *(node->prev ? &(node->prev->next) : &(list->head)) = node->next;
    *(node->next ? &(node->next->prev) : &(list->tail)) = node->prev;
    node->next = NULL;
    node->prev = NULL;
    mem_release(node);
}

void list_clear(list_t* list)
{
    list_node_t* node;
    assert(NULL != list);
    node = list->tail;
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
    list_t* list = (list_t*)p_list;
    assert(NULL != list);
    if (NULL != list->head)
        mem_release(list->head);
}

static void list_node_free(void* p_node)
{
    list_node_t* node = (list_node_t*)p_node;
    assert(NULL != node);
    if (NULL != node->contents)
        mem_release(node->contents);
    if (NULL != node->next)
        mem_release(node->next);
}

