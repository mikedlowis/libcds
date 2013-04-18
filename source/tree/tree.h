/**
    @file tree.h
    @brief An implementation of a binary tree.
    $Revision$
    $HeadURL$
*/
#ifndef TREE_H
#define TREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdbool.h>

/** A node in a tree */
typedef struct {
    void* value; /*< The value of the node in the tree */
    void* left;  /*< Pointer to the left child of the node */
    void* right; /*< Pointer to the right child of the node */
} tree_node_t;

/** A comparison function used to compare node values when looking up or
 * inserting values
 *
 * @param tval The "tree" value. The value stored in the tree.
 * @param fval The "free" value. The value to be inserted, erased, or looked up.
 *
 * @return  0 if the values are equal.
 *         -1 if "tree" value (tval) is less than "free" value (fval).
 *          1 if "tree" value (tval) is greater than "free" value (fval).
 **/
typedef int (*tree_cmp_fn_t)(void* tval,void* fval);

/** A binary tree */
typedef struct {
    tree_cmp_fn_t cmp_fn; /*< Comparison function used to compare values stored in the tree */
    size_t size;          /*< The number of elements currently stored in the tree */
    tree_node_t* root;    /*< Pointer to the root of the tree */
} tree_t;

/**
 * @brief Create a new empty binary tree.
 *
 * @param cmp_fn The function to be used for comparing values.
 *
 * @return Pointer to the newly created tree.
 */
tree_t* tree_new(tree_cmp_fn_t cmp_fn);

/**
 * @brief Create a new tree node with the provided value.
 *
 * @param value The value to be stored in the node.
 *
 * @return Pointer to the newly created node.
 */
tree_node_t* tree_new_node(void* value);


/**
 * @brief Compare the raw pointer values provided.
 *
 * This function is the comparison function used if the user does not provide a
 * function when the tree is initialized.
 *
 * @param tval The "tree" value. The value stored in the tree.
 * @param fval The "free" value. The value to be inserted, erased, or looked up.
 *
 * @return  0 if the values are equal.
 *         -1 if "tree" value (tval) is less than "free" value (fval).
 *          1 if "tree" value (tval) is greater than "free" value (fval).
 */
int tree_cmp_ptrs(void* tval,void* fval);

/**
 * @brief Free the tree and all it's nodes.
 *
 * @param tree The tree to be freed.
 * @param free_values Whether the value of each node should also be freed.
 */
void tree_free(tree_t* tree, bool free_values);

/**
 * @brief Frees the tree node.
 *
 * @param node The node to be freed.
 * @param free_value Whether the value of the node should also be freed.
 */
void tree_free_node(tree_node_t* node, bool free_value);

/**
 * @brief Return whether the tree is empty or not.
 *
 * @param tree The tree in question.
 *
 * @return Whether the tree is empty or not.
 */
bool tree_empty(tree_t* tree);

/**
 * @brief Return the number of elements currently in the tree.
 *
 * @param tree The tree in question.
 *
 * @return The number of elements currently in the tree.
 */
size_t tree_size(tree_t* tree);

/**
 * @brief Return the maximum number of elements that can be stored in a tree.
 *
 * @return The maximum number of elements that can be stored in a tree.
 */
size_t tree_max_size(void);

/**
 * @brief Insert the given element in the given tree.
 *
 * @param tree The tree in which the element will be inserted.
 * @param value The value to insert.
 */
void tree_insert(tree_t* tree, void* value);

/**
 * @brief Lookup the provided value in the provided tree.
 *
 * @param tree The tree in question.
 * @param value Pointer to the value to find.
 *
 * @return Pointer to the matching value or NULL if none found.
 */
void* tree_at(tree_t* tree, void* value);

/**
 * @brief Erase from the tree the first element matching the provided value.
 *
 * @param tree The tree from which the value will be removed.
 * @param value Pointer to the value to erase.
 */
void tree_erase(tree_t* tree, void* value);

/**
 * @brief Erase all values in the tree.
 *
 * @param tree The tree to clear.
 * @param free_values Whether the values should be freed or not.
 */
void tree_clear(tree_t* tree, bool free_values);

#ifdef __cplusplus
}
#endif

#endif /* TREE_H */
