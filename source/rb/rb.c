#include <stdlib.h>

#include "mem.h"
#include "rb.h"

static void rb_tree_free(void* v_tree){
	rb_tree_t* tree = (rb_tree_t*) v_tree;
	if(tree && tree->root) mem_release(tree->root);
}

static void rb_node_free(void* v_node){
	rb_node_t* node = (rb_node_t*) v_node;
	if(node){
		if(node->left) mem_release(node->left);
		if(node->right) mem_release(node->right);
	}
}


rb_node_t* rb_node_new(int contents){
	rb_node_t* node = mem_allocate(sizeof(rb_node_t), &rb_node_free);
	node->left = NULL;
	node->right = NULL;
	node->contents = contents;
	node->color = RED;
	return node;
}

rb_tree_t* rb_tree_new(){
	rb_tree_t* tree = mem_allocate(sizeof(rb_tree_t), &rb_tree_free);
	tree->root = NULL;
	return tree;
}

