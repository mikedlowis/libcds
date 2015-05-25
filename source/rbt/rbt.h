/**
  @file rbt.h
  @brief Implementation of a Red-Black tree.
  */
#ifndef RBT_H
#define RBT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rt.h"

/** node colors */
typedef enum {
    RED = 0,
    BLACK
} rbt_color_t;

/** a function pointer for comparing node contents
  should return -1, 0, or 1 if a is <, ==, or > b, respectively */
typedef int (*comparator_t)(void* p_a, void* p_b);

/** a red-black tree node */
typedef struct rbt_node_t {
    /** pointers to immediate relatives */
    struct rbt_node_t* left;
    struct rbt_node_t* right;
    struct rbt_node_t* parent;
    /** node color */
    rbt_color_t color;
    /** pointer to node contents */
    void* contents;
} rbt_node_t;

/** a red-black tree */
typedef struct {
    /** pointer to the root of the tree */
    rbt_node_t* root;
    /** function pointer for comparing node contents */
    comparator_t comp;
} rbt_t;


/**
 * @brief creates a new red-black tree
 *
 * @param comparator pointer to the comparator function
 *
 * @return pointer to newly created tree
 */
rbt_t* rbt_new(comparator_t comparator);


/**
 * @brief find a value in a red-black tree
 *
 * @param tree  pointer to the tree on which to operate
 * @param value pointer to the data to find
 *
 * @return pointer to the node containing the given value
 *         NULL if the value is present in the tree
 */
rbt_node_t* rbt_lookup(rbt_t* tree, void* value);


/**
 * @brief count the number of nodes in a red-black tree
 *
 * @param tree  pointer to the tree on which to operate
 *
 * @return the number of nodes present in the tree
 */
int rbt_size(rbt_t* tree);

/**
 * @brief insert a value into a red-black tree
 *
 * @param tree  pointer to the tree on which to operate
 * @param value pointer to the value to be inserted
 *
 * @return a pointer to the new node
 */
rbt_node_t* rbt_insert(rbt_t* tree, void* value);


/**
 * @brief removes a value from a red-black tree
 *
 * @param tree  pointer to the tree on which to operate
 * @param value pointer to the value to be removed
 */
void rbt_delete(rbt_t* tree, void* value);

#ifdef __cplusplus
}
#endif

#endif /* RBT_H */

