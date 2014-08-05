#include <stdlib.h>
#include <stdbool.h>

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
	node->parent = NULL;
	node->contents = contents;
	node->color = RED;
	return node;
}

rb_tree_t* rb_tree_new(){
	rb_tree_t* tree = mem_allocate(sizeof(rb_tree_t), &rb_tree_free);
	tree->root = NULL;
	return tree;
}

//leaves are NULL and black implicitly
static rb_color_t node_color(rb_node_t* node){
	return (node ? node->color : BLACK);
}

//NODE:the node to be inserted
static void rb_tree_recolor(rb_node_t* node){
	rb_node_t* parent = node->parent;
	rb_node_t* grandparent = (parent ? parent->parent : NULL);
	rb_node_t* uncle = (grandparent ? (parent == grandparent->left ? grandparent->right : grandparent->left) : NULL);
	if(NULL == parent){
		node->color = BLACK;
	}else if(BLACK == node_color(parent)){
		/* dont need to do anything */
	}else if(node_color(parent) == BLACK && node_color(uncle) == BLACK){
		grandparent->color = RED;
		parent->color = BLACK;
		uncle->color = BLACK;
	}else{
		//TODO
	}
}
static void rb_tree_insert_node(rb_tree_t* tree, rb_node_t* node, rb_node_t* parent){
	if(NULL == parent){ /* inserting root of the tree */
		tree->root = node;
		rb_tree_recolor(node);
	}else if(node->contents < parent->contents){
		if(parent->left){
			rb_tree_insert_node(tree, node, parent->left);
		}else{
			node->parent = parent;
			parent->left = node;
			rb_tree_recolor(node);
		}
	}else{
		if(parent->right){
			rb_tree_insert_node(tree, node, parent->right);
		}else{
			node->parent = parent;
			parent->right = node;
			rb_tree_recolor(node);
		}
	}
}

rb_node_t* rb_tree_insert(rb_tree_t* tree, int value){
	rb_node_t* new_node = rb_node_new(value);
	rb_tree_insert_node(tree, new_node, tree->root);
	return new_node;
}


/* THE FOLLOWING FUNCTIONS (TO EOF) ARE USED FOR TESTING PURPOSES ONLY */

//if path to the left != path to the right, return -1 (invalid)
int count_black_nodes_to_leaf(rb_node_t* node){
	int ret = 0;
	if(node){
		int leftcount = count_black_nodes_to_leaf(node->left);
		int rightcount = count_black_nodes_to_leaf(node->right);
		if(leftcount != rightcount) ret = -1;
		else if(node->color == BLACK) ret = leftcount+1;
		else ret = leftcount;
	}
	return ret;
}

bool rb_node_is_valid(rb_node_t* node, int min_val, int max_val){
	bool ret = true;
	if(node){
		ret &= (node->color == RED || node->color == BLACK);
		if(node->color == RED){
			ret &= ((node_color(node->left) == BLACK) && 
					(node_color(node->right) == BLACK));
		}
		ret &= ( -1 == min_val || node->contents >= min_val);
		ret &= ( -1 == max_val || node->contents <= max_val);
		ret &= rb_node_is_valid(node->left, min_val, node->contents);
		ret &= rb_node_is_valid(node->right, node->contents, max_val);
	}
	return ret;
}

//check the contents of the given tree/node as valid
bool rb_tree_is_valid(rb_tree_t* tree){
	bool ret = true;
	if(tree){
		ret = rb_node_is_valid(tree->root, -1, -1);
		if(tree->root) ret &= (tree->root->color == BLACK);
		ret &= (count_black_nodes_to_leaf(tree->root) != -1);
	}
	return ret;
}

