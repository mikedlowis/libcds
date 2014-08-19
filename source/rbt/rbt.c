#include "mem.h"
#include "rbt.h"

//nodes are compared by memory address by default
int rbt_default_comparator(void* v_a, void* v_b){
	uintptr_t a = (intptr_t)v_a;
	uintptr_t b = (intptr_t)v_b;
	return (a == b ? 0 : (a<b ? -1 : 1 ));
}

/* -------------------------------- */
/*    destructors / constructors    */
/* -------------------------------- */

/* rbt_t */
static void rbt_free(void* v_tree){
	rbt_t* tree = (rbt_t*) v_tree;
	if(tree && tree->root) mem_release(tree->root);
}
rbt_t* rbt_new(comparator_t comparator){
	rbt_t* tree = mem_allocate(sizeof(rbt_t), &rbt_free);
	tree->root = NULL;
	tree->comp = comparator ? comparator : rbt_default_comparator;
	return tree;
}

/* rbt_node_t */
static void rbt_node_free(void* v_node){
	rbt_node_t* node = (rbt_node_t*) v_node;
	if(node){
		mem_release(node->contents);
		if(node->left) mem_release(node->left);
		if(node->right) mem_release(node->right);
	}
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


/* ---------------------------------------- */
/*    informational / querying functions    */
/* ---------------------------------------- */

rbt_color_t rbt_node_color(rbt_node_t* node){
	//leaves are NULL and black implicitly
	return (node ? node->color : BLACK);
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

static rbt_node_t* rightmost_descendant(rbt_node_t* node){
	return (node->right) ? rightmost_descendant(node->right) : node;
}

static int rbt_count(rbt_node_t* node){
	return (!node ? 0 : (1 + rbt_count(node->left) + rbt_count(node->right)));
}
int rbt_count_nodes(rbt_t* tree){
	return rbt_count(tree->root);
}

/* ----------------------------------------- */
/*    generally helpful tree manipulation    */
/* ----------------------------------------- */

static void rbt_node_replace(rbt_t* tree, rbt_node_t* target, rbt_node_t* replacement){
	if(NULL == target->parent) tree->root = replacement;
	else if(target == target->parent->left) target->parent->left = replacement;
	else target->parent->right = replacement;
	if(replacement) replacement->parent = target->parent;
}

typedef enum {
	LEFT = 0, RIGHT
} direction_t;

static void rbt_rotate(rbt_t* tree, rbt_node_t* node, direction_t direction){
	rbt_node_t* edon = (direction == LEFT) ? node->right : node->left;
	if(edon){
		rbt_node_t** edon_side = (direction == LEFT ? &(edon->left) : &(edon->right));
		rbt_node_t** node_side = (direction == LEFT ? &(node->right) : &(node->left));
		rbt_node_replace(tree, node, edon);
		*node_side = *edon_side; //safe to overwrite; points to edon
		if(*edon_side) (*edon_side)->parent = node;
		*edon_side = node;
		node->parent = edon;
	} /* else rotation isn't allowed */
}


/* -------------------- */
/*    insertion code    */
/* -------------------- */

static void rbt_ins_rebalance(rbt_t* tree, rbt_node_t* node, direction_t heavy_side){
	rbt_node_t* parent = node->parent;
	rbt_node_t* grandparent = (parent ? parent->parent : NULL);
	rbt_rotate(tree, grandparent, (heavy_side == LEFT ? RIGHT : LEFT));
	parent->color = BLACK;
	grandparent->color = RED;
}

static void rbt_ins_recolor(rbt_t* tree, rbt_node_t* node){
	rbt_node_t* parent = node->parent;
	rbt_node_t* grandparent = (parent ? parent->parent : NULL);
	rbt_node_t* uncle = (grandparent ? (parent == grandparent->left ? grandparent->right : grandparent->left) : NULL);
	if(NULL == parent){
		node->color = BLACK;
	}else if(RED == rbt_node_color(parent)){
		if(rbt_node_color(uncle) == RED){
			grandparent->color = RED;
			parent->color = BLACK;
			uncle->color = BLACK;
			rbt_ins_recolor(tree, grandparent);
		}else{
			direction_t node_side = (node == parent->left ? LEFT : RIGHT);
			direction_t parent_side = (parent == grandparent->left ? LEFT : RIGHT);
			if(node_side != parent_side){ // "inside" case
				rbt_rotate(tree, parent, parent_side); //transform to "outside" case
				node = parent; //parent now lowest node.
			}
			rbt_ins_rebalance(tree, node, parent_side);
		}
	}
}

static void rbt_insert_node(rbt_t* tree, rbt_node_t* node, rbt_node_t* parent){
	if(NULL == parent){ /* inserting root of the tree */
		tree->root = node;
		rbt_ins_recolor(tree, node);
	}else{
		int c = tree->comp(node->contents, parent->contents);
		rbt_node_t** relevant_child = (c<0 ? &(parent->left) : &(parent->right));
		if(*relevant_child){
			rbt_insert_node(tree, node, *relevant_child);
		}else{
			node->parent = parent;
			*relevant_child = node;
			rbt_ins_recolor(tree, node);
		}
	}
}

rbt_node_t* rbt_insert(rbt_t* tree, void* value){
	rbt_node_t* new_node = rbt_node_new(value);
	rbt_insert_node(tree, new_node, tree->root);
	return new_node;
}


/* ------------------- */
/*    removal  code    */
/* ------------------- */

//node has a count -1 of black nodes to leaves relative to the rest of the tree
static void rbt_del_rebalance(rbt_t* tree, rbt_node_t* node){
	rbt_node_t* parent = node->parent;
	if(parent){
		direction_t node_side = (node == parent->left ? LEFT : RIGHT);
		rbt_node_t* sib = (node_side == LEFT ? parent->right : parent->left);
		//nibling: gender neutral term for niece or nephew.
		rbt_node_t* inside_nibling = sib ? (node_side == LEFT ? sib->left : sib->right) : NULL;
		rbt_node_t* outside_nibling = sib ? (node_side == LEFT ? sib->right : sib->left) : NULL;
		if(RED == rbt_node_color(sib)){
			//rotate so sib is black & recurse w/ new scenario
			rbt_rotate(tree, parent, node_side);
			parent->color = RED;
			sib->color = BLACK;
			rbt_del_rebalance(tree, node);
		}else if(BLACK == rbt_node_color(inside_nibling) && BLACK == rbt_node_color(outside_nibling)){
			//both niblings are black ; can paint sib red & rebalance on parent
			sib->color = RED;
			if(RED == rbt_node_color(parent)) parent->color = BLACK;
			else rbt_del_rebalance(tree, parent);
		}else if(BLACK == rbt_node_color(outside_nibling)){
			//convert "inside" case to "outside" case & recurse w/ new scenario
			rbt_rotate(tree, sib, (node_side == LEFT ? RIGHT : LEFT));
			sib->color = RED;
			inside_nibling->color = BLACK;
			rbt_del_rebalance(tree, node);
		}else{
			rbt_rotate(tree, parent, node_side);
			sib->color = parent->color;
			parent->color = BLACK;
			outside_nibling->color = BLACK;
		}
	}else{
		node->color = BLACK; //TODO: verify this is necessary
	}
}

static void rbt_delete_node(rbt_t* tree, rbt_node_t* node){
	rbt_node_t* descendant = NULL;
	if(node->left && node->right){
		descendant = rightmost_descendant(node->left);
		mem_retain(descendant);
		rbt_delete_node(tree, descendant);
		if(node->left) node->left->parent = descendant;
		if(node->right) node->right->parent = descendant;
		descendant->left = node->left;
		descendant->right = node->right;
		descendant->color = node->color;
	}else if(BLACK == rbt_node_color(node)){
		//black node with at most one non-leaf child
		if(RED == rbt_node_color(node->left) || RED == rbt_node_color(node->right)){
			descendant = node->left ? node->left : node->right;
			descendant->color = BLACK;
		} else {
			rbt_del_rebalance(tree, node);
		}
	}
	rbt_node_replace(tree, node, descendant);
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	mem_release(node);
}

void rbt_delete(rbt_t* tree, void* value){
	rbt_node_t* doomed = rbt_lookup(tree, value);
	if(doomed) rbt_delete_node(tree, doomed);
}

