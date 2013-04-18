/**
  @file tree.c
  @brief See header for details
  $Revision$
  $HeadURL$
  */
#include <stdlib.h>
#include "tree.h"

tree_t* tree_new(tree_cmp_fn_t cmp_fn)
{
    tree_t* tree = (tree_t*)malloc(sizeof(tree_t));
    tree->cmp_fn = (NULL == cmp_fn) ? tree_cmp_ptrs : cmp_fn;
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

void* tree_at(tree_t* tree, void* value)
{
    void* ret_val = NULL;
    tree_node_t* node = tree->root;
    while(node != NULL)
    {
        switch (tree->cmp_fn(node->value, value))
        {
            case 0:
                ret_val = node->value;
                node = NULL;
                break;

            case -1:
                node = node->right;
                break;

            case 1:
                node = node->left;
                break;
        }
    }
    return ret_val;
}

void tree_erase(tree_t* tree, void* value)
{
    //tree_node_t* prev_node = NULL;
    //tree_node_t* curr_node = tree->root;
    //while(node != NULL)
    //{
    //    switch (tree->cmp_fn(node->value, value))
    //    {
    //        case 0:
    //            ret_val = node->value;
    //            node = NULL;
    //            break;

    //        case -1:
    //            node = node->right;
    //            break;

    //        case 1:
    //            node = node->left;
    //            break;
    //    }
    //}
}

void tree_clear(tree_t* tree, bool free_values)
{
    tree->size = 0;
    tree_free_node( tree->root, free_values );
    tree->root = NULL;
}


