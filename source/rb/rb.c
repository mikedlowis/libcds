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

static void rb_tree_rotate_outside_left(rb_tree_t* tree, rb_node_t* node){
	rb_node_t* parent = node->parent;
	rb_node_t* grandparent = (parent ? parent->parent : NULL);
	//rb_node_t* uncle = (grandparent ? (parent == grandparent->left ? grandparent->right : grandparent->left) : NULL);
	rb_node_t* greatgrand = (grandparent ? grandparent->parent : NULL);
	//move parent to grandparent's position:
	//first point greatgrand at parent on the appropriate side:
	if(greatgrand && grandparent == greatgrand->left) greatgrand->left = parent;
	else if(greatgrand && grandparent == greatgrand->right) greatgrand->right = parent;
	//update parent's parent pointer.
	parent->parent = greatgrand;
	//parent->right shouldn't actually be anything.. but save it anyway
	grandparent->left = parent->right; //safe to overwrite gp->left. it is parent.
	parent->right = grandparent;
	grandparent->parent = parent;
	//repair the tree root
	if(tree->root == grandparent) tree->root = parent;
	//repaint nodes as needed:
	parent->color = BLACK;
	grandparent->color = RED;
}

//mirror of above:
static void rb_tree_rotate_outside_right(rb_tree_t* tree, rb_node_t* node){
	rb_node_t* parent = node->parent;
	rb_node_t* grandparent = (parent ? parent->parent : NULL);
	//rb_node_t* uncle = (grandparent ? (parent == grandparent->left ? grandparent->right : grandparent->left) : NULL);
	rb_node_t* greatgrand = (grandparent ? grandparent->parent : NULL);
	//move parent to grandparent's position
	if(greatgrand && grandparent == greatgrand->left) greatgrand->left = parent;
	else if(greatgrand && grandparent == greatgrand->right) greatgrand->right = parent;
	parent->parent = greatgrand;
	//perform swap
	grandparent->right = parent->left; //safe to overwrite gp->right. it is parent.
	parent->left = grandparent;
	grandparent->parent = parent;
	//repair the tree root
	if(tree->root == grandparent) tree->root = parent;
	//repaint nodes
	parent->color = BLACK;
	grandparent->color = RED;
}

//NODE:the node to be inserted
static void rb_tree_recolor(rb_tree_t* tree, rb_node_t* node){
	rb_node_t* parent = node->parent;
	rb_node_t* grandparent = (parent ? parent->parent : NULL);
	rb_node_t* uncle = (grandparent ? (parent == grandparent->left ? grandparent->right : grandparent->left) : NULL);
	if(NULL == parent){
		node->color = BLACK;
	}else if(BLACK == node_color(parent)){
		/* dont need to do anything */
	}else if(node_color(uncle) == RED){
		//parent and uncle are both red. both can be painted black
		grandparent->color = RED;
		parent->color = BLACK;
		uncle->color = BLACK;
		rb_tree_recolor(tree, grandparent);
	}else if(node == parent->right && parent == grandparent->left){
		//parent is red, uncle is black, "inside left" case
		//first rotate node and parent
		grandparent->left = node;
		node->parent = grandparent;
		node->left = parent;
		parent->parent = node;
		parent->right = NULL;
		//tree now transformed to an "outside left" case
		rb_tree_rotate_outside_left(tree, parent);
	}else if(node == parent->left && parent == grandparent->right){
		//parent is red, uncle is black, "inside right" case
		//first rotate node and parent
		grandparent->right = node;
		node->parent = grandparent;
		node->right = parent;
		parent->parent = node;
		parent->left = NULL;
		//tree now transformed to an "outside right" case
		rb_tree_rotate_outside_right(tree, parent);
	}else if(node == parent->left && parent == grandparent->left){
		//parent is red, uncle is black, "outside left" case
		rb_tree_rotate_outside_left(tree, node);
	}else if(node == parent->right && parent == grandparent->right){
		//parent is red, uncle is black, "outside right" case
		rb_tree_rotate_outside_right(tree, node);
	}
}

static void rb_tree_insert_node(rb_tree_t* tree, rb_node_t* node, rb_node_t* parent){
	if(NULL == parent){ /* inserting root of the tree */
		tree->root = node;
		rb_tree_recolor(tree, node);
	}else if(node->contents < parent->contents){
		if(parent->left){
			rb_tree_insert_node(tree, node, parent->left);
		}else{
			node->parent = parent;
			parent->left = node;
			rb_tree_recolor(tree, node);
		}
	}else{
		if(parent->right){
			rb_tree_insert_node(tree, node, parent->right);
		}else{
			node->parent = parent;
			parent->right = node;
			rb_tree_recolor(tree, node);
		}
	}
}

rb_node_t* rb_tree_insert(rb_tree_t* tree, int value){
	rb_node_t* new_node = rb_node_new(value);
	rb_tree_insert_node(tree, new_node, tree->root);
	return new_node;
}


static rb_node_t* rb_lookup_node(rb_node_t* node, int value){
	rb_node_t* ret = NULL;
	if(node){
		if(value == node->contents) ret = node;
		else if(value > node->contents) ret = rb_lookup_node(node->right, value);
		else if(value < node->contents) ret = rb_lookup_node(node->left, value);
	}
	return ret;
}

rb_node_t* rb_tree_lookup(rb_tree_t* tree, int value){
	return rb_lookup_node(tree->root, value);
}

static void rb_tree_delete_node(rb_tree_t* tree, rb_node_t* node){
	(void) tree;
	if(node->left && node->right){
		//has two children. TODO
	}else{
		rb_node_t* parent = node->parent;
		if(RED == node_color(node)){
			if(node == parent->left) parent->left = NULL;
			else parent->right = NULL;
			node->parent = NULL;
			mem_release(node);
		} else if(RED == node_color(node->left) && BLACK == node_color(node->right)){
			//single red child, to the left
			rb_node_t* child = node->left;
			child->parent = parent;
			if(NULL == parent) tree->root = child;
			else if(parent->left == node) parent->left = child;
			else parent->right = child;
			//safe to destroy node->right ; it is a NULL leaf
			child->color = BLACK;
			node->left = NULL;
			node->parent = NULL;
			mem_release(node);
		} else if(RED == node_color(node->right) && BLACK == node_color(node->left)){
			//single red child, to the right
			rb_node_t* child = node->right;
			child->parent = parent;
			if(NULL == parent) tree->root = child;
			else if(parent->left == node) parent->left = child;
			else parent->right = child;
			child->color = BLACK;
			node->right = NULL;
			node->parent = NULL;
			mem_release(node);
		}
	}
}
void rb_tree_delete(rb_tree_t* tree, int value){
	rb_node_t* doomed = rb_lookup_node(tree->root, value);
	if(doomed) rb_tree_delete_node(tree, doomed);
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

