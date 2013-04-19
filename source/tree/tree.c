/**
  @file tree.c
  @brief See header for details
  $Revision$
  $HeadURL$
  */
#include <stdlib.h>
#include "tree.h"

#include <stdio.h>

tree_t* tree_new(tree_cmp_fn_t cmp_fn)
{
    tree_t* tree = (tree_t*)malloc(sizeof(tree_t));
    tree->cmp_fn = (NULL == cmp_fn) ? &tree_cmp_ptrs : cmp_fn;
    tree->size = 0;
    tree->root = NULL;
    return tree;
}

tree_node_t* tree_new_node(void* value)
{
    tree_node_t* node = (tree_node_t*)malloc(sizeof(tree_node_t));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int tree_cmp_ptrs(void* tval,void* fval)
{
    int ret = 0;
    if (tval < fval)
        ret = -1;
    else if (tval > fval)
        ret = 1;
    return ret;
}

void tree_free(tree_t* tree, bool free_values)
{
    if (NULL != tree->root)
        tree_free_node(tree->root, free_values);
    free(tree);
}

void tree_free_node(tree_node_t* node, bool free_value)
{
    if (node->left != NULL)
        tree_free_node(node->left, free_value);
    if (node->right != NULL)
        tree_free_node(node->right, free_value);
    if (free_value)
        free(node->value);
    free(node);
}

bool tree_empty(tree_t* tree)
{
    return (tree_size(tree) == 0);
}

size_t tree_size(tree_t* tree)
{
    return tree->size;
}

size_t tree_max_size(void)
{
    return (size_t)(-1);
}

void tree_insert(tree_t* tree, void* value)
{
    bool finished = false;
    tree_node_t* node = tree->root;
    if (node == NULL)
    {
        tree->root = tree_new_node( value );
        tree->size++;
    }
    else
    {
        while(!finished)
        {
            switch (tree->cmp_fn(node->value, value))
            {
                // If the value is already in the tree
                case 0:
                    // Nothing to do because it's already there.
                    finished = true;
                    break;

                case -1:
                    if (NULL == node->right)
                    {
                        node->right = tree_new_node( value );
                        tree->size++;
                        finished = true;
                    }
                    else
                    {
                        node = node->right;
                    }
                    break;

                case 1:
                    if (NULL == node->left)
                    {
                        node->left = tree_new_node( value );
                        tree->size++;
                        finished = true;
                    }
                    else
                    {
                        node = node->left;
                    }
                    break;
            }
        }
    }
}

void* tree_at(tree_t* tree, void* value)
{
    void* ret_val = NULL;
    tree_node_t* node = tree->root;
    while(node != NULL)
    {
        int cmp_val = tree->cmp_fn(node->value, value);
        if (0 == cmp_val)
        {
            ret_val = node->value;
            node = NULL;
        }
        else
        {
            node = (-1 == cmp_val) ? node->right : node->left;
        }
    }
    return ret_val;
}

void tree_erase(tree_t* tree, void* value, bool free_value)
{
    tree_node_t* prev_node = NULL;
    tree_node_t* curr_node = tree->root;
    while(curr_node != NULL)
    {
        int cmp_val = tree->cmp_fn(curr_node->value, value);
        if (0 == cmp_val)
        {
            // Node to delete has no children
            if ((curr_node->left == NULL) && (curr_node->right == NULL))
            {
                //tree_erase_leaf(prev_node,curr_node);
            }
            // Node to delete has two children
            else if ((curr_node->left != NULL) && (curr_node->right != NULL))
            {
                //tree_erase_inner_node(prev_node,curr_node);
            }
            // Node only has one child
            else
            {
                //tree_erase_node(prev_node,curr_node);
            }
        }
        else
        {
            prev_node = curr_node;
            curr_node = (-1 == cmp_val) ? curr_node->right : curr_node->left;
        }
    }
}

void tree_clear(tree_t* tree, bool free_values)
{
    tree->size = 0;
    tree_free_node( tree->root, free_values );
    tree->root = NULL;
}


