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
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node
{
    void* contents;
    struct node* next;
} sll_node;

/**
 * @brief   Creates a new linked list node with the supplied value.
 *
 * Allocates a new node on the heap and populates the node contents with the
 * supplied contents pointer.
 *
 * @param   contents    The contents of the newly created node.
 *
 * @return  A pointer to the newly created node.
 * */
sll_node* sll_new( void* contents );

/**
 * @brief   Finds and returns the last node in the supplied linked list.
 *
 * @param   list    The linked list to search.
 *
 * @return  Pointer to the last node in the supplied list.
 * */
sll_node* sll_last(sll_node* list);

/**
 * @brief   Return the node at the specified index in a linked list.
 *
 * Loops through the linked list and returns the node in the list at the
 * specified index. Returns NULL if the index is out of range.
 *
 * @param   list    The list to search for the supplied index.
 * @param   index   The index of the node to return.
 *
 * @return  A pointer to the node and the supplied index, NULL if out of range.
 * */
sll_node* sll_get(sll_node* list, int index);

/**
 * @brief   Adds a new node to an existing linked list.
 *
 * @param   list
 * @param   contents
 *
 * @return Pointer to the newly added node.
 * */
sll_node* sll_add( sll_node* list, void* contents );

/**
 * @brief   Inserts a new node in a linked list at the specified index.
 *
 * @param   list
 * @param   index
 * @param   contents
 *
 * @return  Pointer to the newly inserted node, NULL if index is out of range.
 * */
sll_node* sll_insert( sll_node* list, int index, void* contents);

/**
 * @brief   Deletes a node from the supplied list.
 *
 * Deletes the node found at the supplied index from the supplied list and frees
 * the memory used by the node and its contents.
 *
 * @param   list
 * @param   index
 * @param   free_contents Whether or not to also free the contents of the node.
 *
 * @return Pointer to the node that is now at the supplied index.
 * */
sll_node* sll_delete( sll_node* list, int index, int free_contents);

/**
 * @brief   Frees all memory used by a linked list.
 *
 * Loops through the supplied list and frees all nodes. Also frees contents if
 * free_contents is passed TRUE. This is to avoid trying to free memory
 * allocated on the stack.
 *
 * @param   list          The list to be freed.
 * @param   free_contents Whether or not to also free the contents of each node.
 * */
void sll_free( sll_node* list, int free_contents);

/**
 * @brief Returns the number of elements in the list.
 *
 * Loops through the supplied list and returns a count of the number of elements
 * contained in the list.
 *
 * @param list        The list to be counted.
 *
 * @return The number of elements in the list.
 **/
unsigned int sll_length(sll_node* list);

#endif
