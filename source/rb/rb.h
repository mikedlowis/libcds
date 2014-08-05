#ifndef RB_H
#define RB_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	RED = 0,
	BLACK
} rb_color_t;

typedef struct rb_node_t {
	struct rb_node_t* left;
	struct rb_node_t* right;
	rb_color_t color;
	int contents; /* int for development; TODO: make this a void* */
} rb_node_t;

typedef struct {
	rb_node_t* root;
} rb_tree_t;


rb_node_t* rb_node_new(int contents);
rb_tree_t* rb_tree_new();

#ifdef __cplusplus
}
#endif

#endif /* RB_H */

