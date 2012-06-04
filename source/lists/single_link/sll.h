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
#ifndef SLL_H
#define SLL_H

//! A linked list node.
typedef struct sll_node
{
    //! Pointer to the contents the node
    void* contents;
    //! Pointer to next node in the list.
    struct sll_node* next;
} sll_node;

/**
 * @brief Creates a new linked list node with the supplied value.
 *
 * This function allocates a new node and populates the node contents with the
 * supplied contents pointer.
 *
 * @param contents The contents of the newly created node.
 *
 * @return A pointer to the newly created node.
 **/
sll_node* sll_new( void* contents );

/**
 * @brief Finds and returns the first node in the supplied linked list.
 *
 * This function returns a pointer to the first node in the given linked list.
 *
 * @param list The linked list to search.
 *
 * @return Pointer to the last node in the supplied list.
 **/
sll_node* sll_front(sll_node* list);

/**
 * @brief Finds and returns the last node in the supplied linked list.
 *
 * This function returns a pointer to the last node in the given linked list.
 *
 * @param list The linked list to search.
 *
 * @return Pointer to the last node in the supplied list.
 **/
sll_node* sll_back(sll_node* list);

/**
 * @brief   Return the node at the specified index in a linked list.
 *
 * This function loops through the linked list and returns the node in the list
 * at the specified index. Returns NULL if the index is out of range.
 *
 * @param list  The list to search for the supplied index.
 * @param index The index of the node to return.
 *
 * @return A pointer to the node and the supplied index, NULL if out of range.
 **/
sll_node* sll_index(sll_node* list, int index);

/**
 * @brief Adds a new node to the front of an existing linked list.
 *
 * This function creates a new node and pushes it to the beginning of the given
 * list. The newly created node becomes the new head of the list.
 *
 * @param list     The list to operate on.
 * @param contents The contents of the new node.
 *
 * @return Pointer to the newly added node.
 **/
sll_node* sll_push_front( sll_node* list, void* contents );

/**
 * @brief Adds a new node to the end of an existing linked list.
 *
 * This function creates a new node and pushes it to the end of the given list.
 * The newly created node becomes the new tail of the list.
 *
 * @param list     The list to operate on.
 * @param contents The contents of the new node.
 *
 * @return Pointer to the newly added node.
 **/
sll_node* sll_push_back( sll_node* list, void* contents );

/**
 * @brief Removes and returns a pointer to the first element of the list.
 *
 * This function removes the first node from the list and frees it's associated
 * memory. If free_contents is passed a non-zero value then it's contents
 * pointer is also freed. The second node in the list becomes the new head of
 * the list.
 *
 * @param list          The lsit to operate on.
 * @param free_contents Determines whether to free the contents pointer.
 *
 * @return Pointer to the newly added node.
 **/
void sll_pop_front( sll_node* list, int free_contents );

/**
 * @brief Removes and returns a pointer to the last element of the list.
 *
 * This function removes the last node from the list and frees it's associated
 * memory. If free_contents is passed a non-zero value then it's contents
 * pointer is also freed. The second to last node in the list becomes the new
 * tail of the list.
 *
 * @param list          The list to operate on.
 * @param free_contents Determines whether to free the contents pointer.
 *
 * @return Pointer to the newly added node.
 **/
void sll_pop_back( sll_node* list, int free_contents );

/**
 * @brief Inserts a new node in a linked list at the specified index.
 *
 * This function traverses the list to the desired index and inserts a new node
 * with the given contents at that position. The node previously at the desired
 * index becomes the child of the new node.
 *
 * @param list     The list to operate on.
 * @param index    The index where the new node will be inserted.
 * @param contents The contents of the new node.
 *
 * @return Pointer to the newly inserted node, NULL if index is out of range.
 **/
sll_node* sll_insert( sll_node* list, int index, void* contents);

/**
 * @brief Deletes a node from the supplied list.
 *
 * This function traverses the list to the desired index and frees the memory
 * allocated for that node. If the deleted node has a child then the child is
 * reattached to the deleted node's parent. If free_contents is passed a
 * non-zero value then the node's contents pointer is also freed.
 *
 * @param list          The list to operate on.
 * @param index         The index of the node to delete.
 * @param free_contents Whether or not to also free the contents of the node.
 *
 * @return Pointer to the node that is now at the supplied index.
 **/
sll_node* sll_delete( sll_node* list, int index, int free_contents);

/**
 * @brief Frees all memory used by a linked list.
 *
 * This function loops through the supplied list and frees all nodes.
 * Also frees contents if free_contents is passed a non-zero value.
 *
 * @param list          The list to be freed.
 * @param free_contents Whether or not to also free the contents of each node.
 **/
void sll_free( sll_node* list, int free_contents);

/**
 * @brief Returns the number of elements in the list.
 *
 * This function loops through the supplied list and returns a count of the
 * number of elements contained in the list.
 *
 * @param list The list to be counted.
 *
 * @return The number of elements in the list.
 **/
unsigned int sll_length(sll_node* list);

#endif
