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

//TEST FUNCTIONS:
bool rb_tree_is_valid(rb_tree_t* tree);
bool rb_node_is_valid(rb_node_t* node, int min_val, int max_val);

#ifdef __cplusplus
}
#endif

#endif /* RB_H */

