#ifndef RB_H
#define RB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef enum {
	RED = 0,
	BLACK
} rbt_color_t;

typedef enum {
	OK = 0,
	OUT_OF_ORDER,
	BAD_ROOT_COLOR,
	BLACK_NODES_UNBALANCED,
	UNKNOWN_COLOR,
	RED_WITH_RED_CHILD,
	BAD_PARENT_POINTER,
	SELF_REFERENCE,
} rbt_status_t;
 
typedef int (*comparator_t)(void* p_a, void* p_b);

typedef struct rbt_node_t {
	struct rbt_node_t* left;
	struct rbt_node_t* right;
	struct rbt_node_t* parent;
	rbt_color_t color;
	void* contents;
} rbt_node_t;

typedef struct {
	rbt_node_t* root;
	comparator_t comp;
} rbt_t;


rbt_node_t* rbt_node_new(void* contents);
rbt_t* rbt_new(comparator_t comparator);
//returns a pointer to the new node
rbt_node_t* rbt_insert(rbt_t* tree, void* value);
void rbt_delete(rbt_t* tree, void* value);
//look up a node in the tree with the given value
rbt_node_t* rbt_lookup(rbt_t* tree, void* value);

//TEST FUNCTIONS:
rbt_status_t rbt_check_status(rbt_t* tree);
//rbt_status_t rbt_check_node(rbt_node_t* node, void* min_val, void* max_val);

#ifdef __cplusplus
}
#endif

#endif /* RB_H */

