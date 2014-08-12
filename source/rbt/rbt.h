#ifndef RB_H
#define RB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef enum {
	RED = 0,
	BLACK
} rb_color_t;

typedef enum {
	OK = 0,
	OUT_OF_ORDER,
	BAD_ROOT_COLOR,
	BLACK_NODES_UNBALANCED,
	UNKNOWN_COLOR,
	RED_WITH_RED_CHILD,
	BAD_PARENT_POINTER,
	SELF_REFERENCE,
} rb_status_t;

typedef struct rb_node_t {
	struct rb_node_t* left;
	struct rb_node_t* right;
	struct rb_node_t* parent;
	rb_color_t color;
	int contents; /* int for development; TODO: make this a void* */
} rb_node_t;

typedef struct {
	rb_node_t* root;
} rb_tree_t;


rb_node_t* rb_node_new(int contents);
rb_tree_t* rb_tree_new();
//returns a pointer to the new node
rb_node_t* rb_tree_insert(rb_tree_t* tree, int value);
void rb_tree_delete(rb_tree_t* tree, int value);
//look up a node in the tree with the given value
rb_node_t* rb_tree_lookup(rb_tree_t* tree, int value);

//TEST FUNCTIONS:
rb_status_t rb_tree_is_valid(rb_tree_t* tree);
rb_status_t rb_node_is_valid(rb_node_t* node, int min_val, int max_val);

#ifdef __cplusplus
}
#endif

#endif /* RB_H */

