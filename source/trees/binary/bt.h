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
#ifndef BT_H
#define BT_H

//! A function pointer for a comparison function.
typedef int (* bt_compare_func) (void*,void*);

//! A binary tree node.
typedef struct bt_node
{
    //! The contents of the tree node.
    void* contents;
    //! The left child of the tree node.
    struct bt_node* left;
    //! the right child of the tree node.
    struct bt_node* right;
} bt_node;

//! A binary tree
typedef struct bt_tree
{
    //! The root of the binary tree
    bt_node* root;
    //! The function used to compare data
    bt_compare_func compare;
} bt_tree;

/**
 * @brief Creates a new empty binary tree.
 *
 * This function creates a new empty binary search tree with the given
 * comparison function. The comparison function will be used during searching,
 * insertions, and deletions, to find and traverse the tree.
 *
 * @param compare The function to use for comparing items in the tree.
 *
 * @return Pointer to the newly created tree.
 **/
bt_tree* bt_new(bt_compare_func compare);

/**
 * @brief Frees the memory allocated for all nodes of a tree.
 *
 * This function frees all memory associated with the given tree. If
 * free_contents has a non-zero value then the contents pointer of each node
 * will aslo be freed.
 *
 * @param tree          The tree to be freed.
 * @param free_contents Determines whether the contents pointers will be freed.
 **/
void bt_free(bt_tree* tree, int free_contents);

/**
 * @brief Compares the value of two pointers.
 *
 * This function takes two pointers and compares their values returning an
 * integral value representing the result of the comparison. A return value of
 * zero indicates the pointers are equal. A positive value indicates that obj2
 * is greater than obj1 and a negative value indicates the opposite.
 *
 * @param obj1 The first object to be compared.
 * @param obj2 The second object to be compared.
 *
 * @return The result of the comparison.
 **/
int bt_compare_ptr(void* obj1, void* obj2);

/**
 * @brief Inserts a new node into the tree.
 *
 * This function uses the tree's compare function to traverse the tree until an
 * existing node with the given data is found or until a leaf node is reached.
 * If a node exists containing the given data then no insertion is performed.
 * If a leaf node is reached then the a new leaf node is created and set as the
 * left or right child of that leaf node.
 *
 * @param tree The tree in which the node will be inserted.
 * @param data The data that the new node will contain.
 **/
void bt_insert(bt_tree* tree, void* data);

/**
 * @brief Deletes a node for the tree.
 *
 * This function uses the tree's compare function to search the tree for a node
 * containing the given data. If a node containing the data is found then the
 * node is freed otherwise no deletion is performed. If free_contents is passed
 * a non-zero value then the contents pointer of the node is also freed.
 *
 * @param tree          The tree from which the node will be deleted.
 * @param data          The data to search for in the tree.
 * @param free_contents Determines whether the contents pointer will be freed.
 **/
void bt_delete(bt_tree* tree, void* data, int free_contents);

/**
 * @brief Finds and returns the data from a node containing the given data.
 *
 * This function uses the tree's compare function to search the tree for a node
 * containing the given data. If a node containing the given data is found then
 * the pointer to the contents of the node is returned. Otherwise a null
 * pointer is returned.
 *
 * @param tree The tree to be searched.
 * @param data The data to be searched for.
 *
 * @return Pointer to the found data.
 **/
void* bt_find(bt_tree* tree, void* data);

#endif
