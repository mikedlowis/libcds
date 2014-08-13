#include <stdlib.h>
#include <stdbool.h>

#include "mem.h"
#include "rbt.h"

static void rbt_free(void* v_tree){
	rbt_t* tree = (rbt_t*) v_tree;
	if(tree && tree->root) mem_release(tree->root);
}

static void rbt_node_free(void* v_node){
	rbt_node_t* node = (rbt_node_t*) v_node;
	if(node){
		mem_release(node->contents);
		if(node->left) mem_release(node->left);
		if(node->right) mem_release(node->right);
	}
}

static int rbt_default_comparator(void* a, void* b){
	return (a == b ? 0 : (a<b ? -1 : 1 ));
}

rbt_node_t* rbt_node_new(void* contents){
	rbt_node_t* node = mem_allocate(sizeof(rbt_node_t), &rbt_node_free);
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->contents = contents;
	node->color = RED;
	return node;
}

rbt_t* rbt_new(comparator_t comparator){
	rbt_t* tree = mem_allocate(sizeof(rbt_t), &rbt_free);
	tree->root = NULL;
	tree->comp = comparator ? comparator : rbt_default_comparator;
	return tree;
}

//leaves are NULL and black implicitly
static rbt_color_t node_color(rbt_node_t* node){
	return (node ? node->color : BLACK);
}

static void rotate_right(rbt_t* tree, rbt_node_t* node){
	rbt_node_t* edon = node->left;
	if(edon) {
		//attach edon in node's place:
		if(NULL == node->parent) tree->root = edon;
		else if(node->parent->left == node) node->parent->left = edon;
		else node->parent->right = edon;
		edon->parent = node->parent;
		//reattach edon's right to node's left
		//safe to overwrite node->left : is edon
		node->left = edon->right;
		if(edon->right) edon->right->parent = node;
		//attach node to edon
		edon->right = node;
		node->parent = edon;
	} /* else something went wrong... */
}

static void rotate_left(rbt_t* tree, rbt_node_t* node){
	rbt_node_t* edon = node->right;
	if(edon) {
		//attach edon in node's place:
		if(NULL == node->parent) tree->root = edon;
		else if(node->parent->left == node) node->parent->left = edon;
		else node->parent->right = edon;
		edon->parent = node->parent;
		//reattach edon's left to node's right
		//safe to overwrite node->right : is edon
		node->right = edon->left;
		if(edon->left) edon->left->parent = node;
		//attach node to edon
		edon->left = node;
		node->parent = edon;
	} /* else something went wrong... */
}

static void rbt_rotate_outside_left(rbt_t* tree, rbt_node_t* node){
	rbt_node_t* parent = node->parent;
	rbt_node_t* grandparent = (parent ? parent->parent : NULL);
	rotate_right(tree, grandparent);
	parent->color = BLACK;
	grandparent->color = RED;
}

//mirror of above:
static void rbt_rotate_outside_right(rbt_t* tree, rbt_node_t* node){
	rbt_node_t* parent = node->parent;
	rbt_node_t* grandparent = (parent ? parent->parent : NULL);
	rotate_left(tree, grandparent);
	parent->color = BLACK;
	grandparent->color = RED;
}

//NODE:the node to be inserted
static void rbt_ins_recolor(rbt_t* tree, rbt_node_t* node){
	rbt_node_t* parent = node->parent;
	rbt_node_t* grandparent = (parent ? parent->parent : NULL);
	rbt_node_t* uncle = (grandparent ? (parent == grandparent->left ? grandparent->right : grandparent->left) : NULL);
	if(NULL == parent){
		node->color = BLACK;
	}else if(BLACK == node_color(parent)){
		/* dont need to do anything */
	}else if(node_color(uncle) == RED){
		//parent and uncle are both red. both can be painted black
		grandparent->color = RED;
		parent->color = BLACK;
		uncle->color = BLACK;
		rbt_ins_recolor(tree, grandparent);
	}else if(node == parent->right && parent == grandparent->left){
		//parent is red, uncle is black, "inside left" case
		//first rotate node and parent
		rotate_left(tree, parent);
		//tree now transformed to an "outside left" case
		rbt_rotate_outside_left(tree, parent);
	}else if(node == parent->left && parent == grandparent->right){
		//parent is red, uncle is black, "inside right" case
		//first rotate node and parent
		rotate_right(tree, parent);
		//tree now transformed to an "outside right" case
		rbt_rotate_outside_right(tree, parent);
	}else if(node == parent->left && parent == grandparent->left){
		//parent is red, uncle is black, "outside left" case
		rbt_rotate_outside_left(tree, node);
	}else if(node == parent->right && parent == grandparent->right){
		//parent is red, uncle is black, "outside right" case
		rbt_rotate_outside_right(tree, node);
	}
}

static void rbt_insert_node(rbt_t* tree, rbt_node_t* node, rbt_node_t* parent){
	if(NULL == parent){ /* inserting root of the tree */
		tree->root = node;
		rbt_ins_recolor(tree, node);
	//}else if(node->contents < parent->contents){
	}else if(tree->comp(node->contents, parent->contents) < 0){
		if(parent->left){
			rbt_insert_node(tree, node, parent->left);
		}else{
			node->parent = parent;
			parent->left = node;
			rbt_ins_recolor(tree, node);
		}
	}else{
		if(parent->right){
			rbt_insert_node(tree, node, parent->right);
		}else{
			node->parent = parent;
			parent->right = node;
			rbt_ins_recolor(tree, node);
		}
	}
}

rbt_node_t* rbt_insert(rbt_t* tree, void* value){
	rbt_node_t* new_node = rbt_node_new(value);
	rbt_insert_node(tree, new_node, tree->root);
	return new_node;
}


static rbt_node_t* rbt_lookup_node(rbt_t* tree, rbt_node_t* node, void* value){
	rbt_node_t* ret = NULL;
	if(node){
		int c = tree->comp(value, node->contents);
		if(c == 0) ret = node;
		else if(c > 0) ret = rbt_lookup_node(tree, node->right, value);
		else if(c < 0) ret = rbt_lookup_node(tree, node->left, value);
	}
	return ret;
}

rbt_node_t* rbt_lookup(rbt_t* tree, void* value){
	return rbt_lookup_node(tree, tree->root, value);
}

//node has a count -1 of black nodes to leaves relative to the rest of the tree
static void rbt_del_rebalance(rbt_t* tree, rbt_node_t* node){
	rbt_node_t* parent = node->parent;
	if(parent){
		rbt_node_t* sib = (node == parent->left ? parent->right : parent->left);
		if(RED == node_color(sib)){
			//if sibbling is red, rotate to make sibbling black
			if(node == parent->left) rotate_left(tree, parent);
			else rotate_right(tree, parent);
			parent->color = RED;
			sib->color = BLACK;
			//recurse with new sibbling / parent
			rbt_del_rebalance(tree, node);
		}else if(BLACK == node_color(sib->left) && BLACK == node_color(sib->right)){
			sib->color = RED;
			if(RED == node_color(parent)) parent->color = BLACK;
			//recurse to balance parent
			else rbt_del_rebalance(tree, parent);
		}else if(node == parent->left && BLACK == node_color(sib->right)){
			//convert "inside" case to "outside" case
			sib->left->color = BLACK;
			sib->color = RED;
			rotate_right(tree, sib);
			rbt_del_rebalance(tree, node);
		}else if(node == parent->left && RED == node_color(sib->right)){
			rotate_left(tree, parent);
			sib->color = parent->color;
			parent->color = BLACK;
			sib->right->color = BLACK;
		}else if(node == parent->right && BLACK == node_color(sib->left)){
			//convert "inside" case to "outside" case
			sib->right->color = BLACK;
			sib->color = RED;
			rotate_left(tree, sib);
			rbt_del_rebalance(tree, node);
		}else{
			rotate_right(tree, parent);
			sib->color = parent->color;
			parent->color = BLACK;
			sib->left->color = BLACK;
		}
	}else{
		node->color = BLACK; //TODO: verify this is necessary
	}
}

static rbt_node_t* rightmost_descendent(rbt_node_t* node){
	return (node->right) ? rightmost_descendent(node->right) : node;
}

static void rbt_delete_node(rbt_t* tree, rbt_node_t* node){
	(void) tree;
	if(node->left && node->right){
		rbt_node_t* parent = node->parent;
		rbt_node_t* replacement = rightmost_descendent(node->left);
		mem_retain(replacement);
		rbt_delete_node(tree, replacement);
		if(node->left) node->left->parent = replacement;
		if(node->right) node->right->parent = replacement;
		replacement->left = node->left;
		replacement->right = node->right;
		replacement->parent = node->parent;
		replacement->color = node->color;
		if(NULL == parent) tree->root = replacement;
		else if(node == parent->left) parent->left = replacement;
		else parent->right = replacement;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		mem_release(node);
	}else{
		//node has at most one non-leaf child
		rbt_node_t* parent = node->parent;
		if(RED == node_color(node)){
			//node is red and has only leaf children or tree is invalid.
			if(node == parent->left) parent->left = NULL;
			else parent->right = NULL;
			node->parent = NULL;
			mem_release(node);
		} else if(RED == node_color(node->left) && BLACK == node_color(node->right)){
			//single red child, to the left
			rbt_node_t* child = node->left;
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
			rbt_node_t* child = node->right;
			child->parent = parent;
			if(NULL == parent) tree->root = child;
			else if(parent->left == node) parent->left = child;
			else parent->right = child;
			child->color = BLACK;
			node->right = NULL;
			node->parent = NULL;
			mem_release(node);
		} else if(node == tree->root){
			//at most one child & no red children :: no children.
			tree->root = NULL;
			//pointers should already be null.
			mem_release(node);
		} else if(RED == node_color(node->parent)){
			node->parent = NULL;
			if(parent->right == node){
				rbt_node_t* sib = parent->left;
				parent->right = NULL;
				if(sib->right && !sib->left){
					rotate_left(tree, sib);
					parent->color = BLACK;
				}
				rotate_right(tree, parent);
			} else {
				rbt_node_t* sib = parent->right;
				parent->left = NULL;
				if(sib->left && !sib->right){
					rotate_right(tree, sib);
					parent->color = BLACK;
				}
				rotate_left(tree, parent);
			}
			mem_release(node);
		} else if(node == parent->right && (parent->left->left || parent->left->right)){
			//node is black. parent is black. node is parent's right child.
			//sibbling has at least one non-leaf child
			rbt_node_t* sib = parent->left;
			//remove/release the node
			parent->right = NULL;
			node->parent = NULL;
			mem_release(node);
			//rebalance the tree
			//fix sibbling if red first
			if(RED == node_color(sib)){
				sib->color = BLACK;
				sib->right->color = RED;
				//sib->left->color = RED; //unnecessary; gets overwritten anyway.
			}
			//rotate "inside" case to "outside"
			if(sib->right && !sib->left){
				sib->right->color = BLACK;
				rotate_left(tree, sib);
			}
			if(sib->left) sib->left->color = BLACK;
			rotate_right(tree, parent);
		} else if(node == parent->left && (parent->right->left || parent->right->right)){
			//node is black. parent is black. node is parent's left child.
			//sibbling has at least one non-leaf child
			rbt_node_t* sib = parent->right;
			//remove/release the node
			parent->left = NULL;
			node->parent = NULL;
			mem_release(node);
			//rebalance the tree
			//fix sibbling if red first
			if(RED == node_color(sib)){
				sib->color = BLACK;
				sib->left->color = RED;
				//sib->right->color = RED; //unnecessary; gets overwritten anyway.
			}
			//rotate "inside" case to "outside"
			if(sib->left && !sib->right){
				sib->left->color = BLACK;
				rotate_right(tree, sib);
			}
			if(sib->right) sib->right->color = BLACK;
			rotate_left(tree, parent);
		} else if(node == parent->right){
			//node is black, parent is black, sibbling has no children
			rbt_node_t* sib = parent->left;
			//remove/release the node;
			parent->right = NULL;
			node->parent = NULL;
			mem_release(node);
			//rebalance the tree
			sib->color = RED;
			rbt_del_rebalance(tree, parent);
		} else {
			//node is black, parent is black, sibbling has no children
			rbt_node_t* sib = parent->right;
			//remove/release the node;
			parent->left = NULL;
			node->parent = NULL;
			mem_release(node);
			//rebalance the tree
			sib->color = RED;
			rbt_del_rebalance(tree, parent);
		}
	}
}
void rbt_delete(rbt_t* tree, void* value){
	rbt_node_t* doomed = rbt_lookup(tree, value);
	if(doomed) rbt_delete_node(tree, doomed);
}

/* THE FOLLOWING FUNCTIONS (TO EOF) ARE USED FOR TESTING PURPOSES ONLY */

//if path to the left != path to the right, return -1 (invalid)
int count_black_nodes_to_leaf(rbt_node_t* node){
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

static rbt_status_t rbt_check_node(rbt_t* tree, rbt_node_t* node, void* min_val, void* max_val){
	rbt_status_t ret = OK;
	void* neg1 = mem_box(-1);
	if(node){
		if(node->color != RED && node->color != BLACK) ret = UNKNOWN_COLOR;
		else if(node->color == RED && (node_color(node->left) != BLACK && node_color(node->right) != BLACK))
			ret = RED_WITH_RED_CHILD;
		else if(tree->comp(min_val, neg1) > 0 && tree->comp(node->contents, min_val) < 0) ret = OUT_OF_ORDER;
		else if(tree->comp(max_val, neg1) > 0 && tree->comp(node->contents, max_val) > 0) ret = OUT_OF_ORDER;
		else if(node->left == node || node->right == node) ret = SELF_REFERENCE;
		else if(node->left && node->left->parent != node) ret = BAD_PARENT_POINTER;
		else if(node->right && node->right->parent != node) ret = BAD_PARENT_POINTER;
		if(ret == OK) ret = rbt_check_node(tree, node->left, min_val, node->contents);
		if(ret == OK) ret = rbt_check_node(tree, node->right, node->contents, max_val);
	}
	mem_release(neg1);
	return ret;
}

//check the contents of the given tree/node as valid
rbt_status_t rbt_check_status(rbt_t* tree){
	rbt_status_t ret = OK;
	void* neg1 = mem_box(-1);
	if(tree){
		ret = rbt_check_node(tree, tree->root, neg1, neg1);
		if(ret == OK && tree->root && tree->root->parent) ret = BAD_PARENT_POINTER;
		if(ret == OK && node_color(tree->root) != BLACK) ret = BAD_ROOT_COLOR;
		if(ret == OK && count_black_nodes_to_leaf(tree->root) == -1) ret = BLACK_NODES_UNBALANCED;
	}
	mem_release(neg1);
	return ret;
}

