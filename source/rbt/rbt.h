#ifndef RB_H
#define RB_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	RED = 0,
	BLACK
} rbt_color_t;
 
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

rbt_t* rbt_new(comparator_t comparator);
rbt_node_t* rbt_node_new(void* contents);
rbt_color_t rbt_node_color(rbt_node_t* ndoe);
rbt_node_t* rbt_lookup(rbt_t* tree, void* value);
//returns a pointer to the new node
rbt_node_t* rbt_insert(rbt_t* tree, void* value);
void rbt_delete(rbt_t* tree, void* value);
//look up a node in the tree with the given value

#ifdef __cplusplus
}
#endif

#endif /* RB_H */

