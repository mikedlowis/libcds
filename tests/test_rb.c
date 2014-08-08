// Unit Test Framework Includes
#include "test.h"

#include "rb.h"
#include "mem.h"

static void test_setup(void) { }
//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
TEST_SUITE(RB) {
	//-------------------------------------------------------------------------
	// Test the rb_node_new function
	//-------------------------------------------------------------------------
	TEST(Verify_rb_node_new_returns_a_new_node){
		rb_node_t* node = rb_node_new(42);
		CHECK(NULL != node);
		CHECK(NULL == node->left);
		CHECK(NULL == node->right);
		CHECK(NULL == node->parent);
		CHECK(42 == node->contents);
		CHECK(OK == rb_node_is_valid(node, -1, -1));
		mem_release(node);
	}

	//-------------------------------------------------------------------------
	// Test the rb_tree_new function
	//-------------------------------------------------------------------------
	TEST(Verify_rb_tree_new_returns_an_empty_red_black_tree){
		rb_tree_t* tree = rb_tree_new();
		CHECK(NULL != tree);
		CHECK(NULL == tree->root);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}

	//-------------------------------------------------------------------------
	// Test the test function. testception.
	//-------------------------------------------------------------------------
	TEST(Verify_null_and_empty_trees_are_considered_valid){
		rb_tree_t* tree = NULL;
		CHECK(OK == rb_tree_is_valid(tree));
		tree = rb_tree_new();
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_checks_root_is_always_black_property){
		rb_tree_t* tree = rb_tree_new();
		rb_tree_insert(tree, 88);
		CHECK(BLACK == tree->root->color);
		CHECK(OK == rb_tree_is_valid(tree));
		tree->root->color = RED;
		CHECK(BAD_ROOT_COLOR == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_nodes_not_sorted_two_nodes){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_node_new(42);
		rb_node_t* node2 = rb_node_new(88);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = NULL;
		node1->left = node2;
		node1->right = NULL;
		node2->color = RED;
		node2->parent = node1;
		node2->left = NULL;
		node2->right = NULL;
		CHECK(OUT_OF_ORDER == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_nodes_not_sorted_four_nodes){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_node_new(42);
		rb_node_t* node2 = rb_node_new(88);
		rb_node_t* node3 = rb_node_new(25);
		rb_node_t* node4 = rb_node_new(99);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = NULL;
		node1->left = node3;
		node1->right = node2;
		node2->color = BLACK;
		node2->parent = node1;
		node2->left = node4;
		node2->right = NULL;
		node3->color = BLACK;
		node3->parent = node1;
		node3->left = NULL;
		node3->right = NULL;
		node4->color = RED;
		node4->parent = node2;
		node4->left = NULL;
		node4->right = NULL;
		CHECK(OUT_OF_ORDER == rb_tree_is_valid(tree));
		node2->left = NULL;
		node2->right = node4;
		CHECK(OK == rb_tree_is_valid(tree));
		node1->left = node2;
		node1->right = node3;
		CHECK(OUT_OF_ORDER == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_black_nodes_are_unbalanced_two_nodes){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_node_new(42);
		rb_node_t* node2 = rb_node_new(88);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = NULL;
		node1->left = NULL;
		node1->right = node2;
		node2->color = BLACK;
		node2->parent = node1;
		node2->left = NULL;
		node2->right = NULL;
		CHECK(BLACK_NODES_UNBALANCED == rb_tree_is_valid(tree));
		node2->color = RED;
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_black_nodes_are_unbalanced_three_nodes){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_node_new(42);
		rb_node_t* node2 = rb_node_new(22);
		rb_node_t* node3 = rb_node_new(88);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = NULL;
		node1->left = node2;
		node1->right = node3;
		node2->color = RED;
		node2->parent = node1;
		node2->left = NULL;
		node2->right = NULL;
		node3->color = BLACK;
		node3->parent = node1;
		node3->left = NULL;
		node3->right = NULL;
		CHECK(BLACK_NODES_UNBALANCED == rb_tree_is_valid(tree));
		node2->color = BLACK;
		node3->color = RED;
		CHECK(BLACK_NODES_UNBALANCED == rb_tree_is_valid(tree));
		node2->color = BLACK;
		node3->color = BLACK;
		CHECK(OK == rb_tree_is_valid(tree));
		node2->color = RED;
		node3->color = RED;
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_black_nodes_are_unbalanced_four_nodes){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_node_new(42);
		rb_node_t* node2 = rb_node_new(22);
		rb_node_t* node3 = rb_node_new(88);
		rb_node_t* node4 = rb_node_new(33);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = NULL;
		node1->left = node2;
		node1->right = node3;
		node2->color = RED;
		node2->parent = node1;
		node2->left = NULL;
		node2->right = node4;
		node3->color = BLACK;
		node3->parent = node1;
		node3->left = NULL;
		node3->right = NULL;
		node4->color = BLACK;
		node4->parent = node2;
		node4->left = NULL;
		node4->right = NULL;
		CHECK(BLACK_NODES_UNBALANCED == rb_tree_is_valid(tree));
		node2->color = BLACK;
		node3->color = RED;
		CHECK(BLACK_NODES_UNBALANCED == rb_tree_is_valid(tree));
		node4->color = RED;
		CHECK(BLACK_NODES_UNBALANCED == rb_tree_is_valid(tree));
		node2->color = BLACK;
		node3->color = BLACK;
		node4->color = BLACK;
		CHECK(BLACK_NODES_UNBALANCED == rb_tree_is_valid(tree));
		node4->color = RED;
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_node_is_unvalid_color){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_node_new(42);
		rb_node_t* node2 = rb_node_new(88);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = NULL;
		node1->right = node2;
		node1->left = NULL;
		node2->color = 42;
		node2->parent = node1;
		node2->right = NULL;
		node2->left = NULL;
		CHECK(UNKNOWN_COLOR == rb_tree_is_valid(tree));
		node2->color = RED;
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_root_parent_pointer_is_not_null){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_node_new(42);
		rb_node_t* node2 = rb_node_new(88);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = node2;
		node1->left = NULL;
		node1->right = node2;
		node2->color = RED;
		node2->parent = node1;
		node2->left = NULL;
		node2->right = NULL;
		CHECK(BAD_PARENT_POINTER == rb_tree_is_valid(tree));
		node1->parent = NULL;
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_node_parent_poitners_are_wrong_two_nodes){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_node_new(42);
		rb_node_t* node2 = rb_node_new(88);
		rb_node_t* node3 = rb_node_new(99);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = NULL;
		node1->left = NULL;
		node1->right = node2;
		node2->color = RED;
		node2->parent = node1;
		node2->left = NULL;
		node2->right = NULL;
		CHECK(OK == rb_tree_is_valid(tree));
		node2->parent = node3;
		CHECK(BAD_PARENT_POINTER == rb_tree_is_valid(tree));
		node2->parent = NULL;
		CHECK(BAD_PARENT_POINTER == rb_tree_is_valid(tree));
		node2->parent = node1;
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_node_parent_poitners_are_wrong_four_nodes){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_node_new(42);
		rb_node_t* node2 = rb_node_new(22);
		rb_node_t* node3 = rb_node_new(88);
		rb_node_t* node4 = rb_node_new(33);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = NULL;
		node1->left = node2;
		node1->right = node3;
		node2->color = BLACK;
		node2->parent = node1;
		node2->left = NULL;
		node2->right = node4;
		node3->color = BLACK;
		node3->parent = node1;
		node3->left = NULL;
		node3->right = NULL;
		node4->color = RED;
		node4->parent = node2;
		node4->left = NULL;
		node4->right = NULL;
		CHECK(OK == rb_tree_is_valid(tree));
		node4->parent = node1;
		CHECK(BAD_PARENT_POINTER == rb_tree_is_valid(tree));
		node4->parent = NULL;
		CHECK(BAD_PARENT_POINTER == rb_tree_is_valid(tree));
		node4->parent = node4;
		CHECK(BAD_PARENT_POINTER == rb_tree_is_valid(tree));
		node4->parent = node2;
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_node_points_to_itself){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_node_new(42);
		rb_node_t* node2 = rb_node_new(22);
		rb_node_t* node3 = rb_node_new(88);
		rb_node_t* node4 = rb_node_new(33);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = NULL;
		node1->left = node2;
		node1->right = node3;
		node2->color = BLACK;
		node2->parent = node1;
		node2->left = NULL;
		node2->right = node4;
		node3->color = BLACK;
		node3->parent = node1;
		node3->left = NULL;
		node3->right = NULL;
		node4->color = RED;
		node4->parent = node2;
		node4->left = NULL;
		node4->right = NULL;
		CHECK(OK == rb_tree_is_valid(tree));
		node4->right = node4;
		CHECK(SELF_REFERENCE == rb_tree_is_valid(tree));
		node4->right = NULL;
		node2->left = node2;
		CHECK(SELF_REFERENCE == rb_tree_is_valid(tree));
		node2->left = NULL;
		node2->right = node2;
		CHECK(SELF_REFERENCE == rb_tree_is_valid(tree));
		node2->right = node4;
		node3->left = node3;
		CHECK(SELF_REFERENCE == rb_tree_is_valid(tree));
		node3->left = NULL;
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}

	//-------------------------------------------------------------------------
	// Test insert functions
	//-------------------------------------------------------------------------
	TEST(Verify_rb_insert_to_an_empty_list_assigns_root){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node = rb_tree_insert(tree, 42);
		CHECK(NULL != node);
		CHECK(tree->root == node);
		CHECK(42 == node->contents);
		CHECK(NULL == node->left);
		CHECK(NULL == node->right);
		CHECK(NULL == node->parent);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_rb_insert_node_to_root_left_works){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* root = rb_tree_insert(tree, 42);
		rb_node_t* node1 = rb_tree_insert(tree, 31);
		CHECK(NULL != root);
		CHECK(NULL != node1);
		CHECK(tree->root == root);
		CHECK(root == node1->parent);
		CHECK(31 == node1->contents);
		CHECK(node1 == root->left);
		CHECK(NULL == root->right);
		CHECK(RED == node1->color);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_rb_insert_node_to_root_right_works){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* root = rb_tree_insert(tree, 42);
		rb_node_t* node2 = rb_tree_insert(tree, 64);
		CHECK(NULL != root);
		CHECK(NULL != node2);
		CHECK(tree->root == root);
		CHECK(root == node2->parent);
		CHECK(64 == node2->contents);
		CHECK(node2 == root->right);
		CHECK(NULL == root->left);
		CHECK(RED == node2->color);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_rb_insert_first_level_works){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* root = rb_tree_insert(tree, 42);
		rb_node_t* node1 = rb_tree_insert(tree, 31);
		rb_node_t* node2 = rb_tree_insert(tree, 64);
		CHECK(NULL != root);
		CHECK(NULL != node1);
		CHECK(NULL != node2);
		CHECK(tree->root == root);
		CHECK(root == node1->parent);
		CHECK(root == node2->parent);
		CHECK(31 == node1->contents);
		CHECK(64 == node2->contents);
		CHECK(node1 == root->left);
		CHECK(node2 == root->right);
		CHECK(RED == node1->color);
		CHECK(RED == node2->color);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_rb_insert_below_full_first_level_works){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* root = rb_tree_insert(tree, 42);
		rb_node_t* node1 = rb_tree_insert(tree, 31);
		rb_node_t* node2 = rb_tree_insert(tree, 64);
		rb_node_t* node3 = rb_tree_insert(tree, 15);
		CHECK(NULL != node3);
		CHECK(15 == node3->contents);
		CHECK(node1->left == node3);
		CHECK(NULL == node3->left);
		CHECK(NULL == node3->right);
		CHECK(BLACK == root->color);
		CHECK(BLACK == node1->color);
		CHECK(BLACK == node2->color);
		CHECK(RED == node3->color);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_rb_insert_parent_uncle_mismatch_outside_left){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42);
		rb_node_t* node2 = rb_tree_insert(tree, 32);
		CHECK(node1 == tree->root);
		CHECK(node2 == tree->root->left);
		CHECK(NULL == tree->root->right);
		CHECK(RED == node2->color);
		//tree->root->right == NULL ; black implicitly
		rb_node_t* node3 = rb_tree_insert(tree, 15);
		CHECK(NULL != node3);
		CHECK(node2 == tree->root);
		//check node2 fields 
		CHECK(node3 == node2->left);
		CHECK(node1 == node2->right);
		CHECK(NULL == node2->parent);
		CHECK(BLACK == node2->color);
		CHECK(32 == node2->contents);
		//check node1 fields
		CHECK(NULL == node1->left);
		CHECK(NULL == node1->right);
		CHECK(node2 == node1->parent);
		CHECK(RED == node1->color);
		CHECK(42 == node1->contents);
		//check node3 fields
		CHECK(NULL == node3->left);
		CHECK(NULL == node3->right);
		CHECK(node2 == node3->parent);
		CHECK(RED == node3->color);
		CHECK(15 == node3->contents);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_rb_insert_parent_uncle_mismatch_outside_right){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42);
		rb_node_t* node2 = rb_tree_insert(tree, 53);
		CHECK(node1 == tree->root);
		CHECK(node2 == tree->root->right);
		CHECK(NULL == tree->root->left);
		CHECK(RED == node2->color);
		rb_node_t* node3 = rb_tree_insert(tree, 99);
		CHECK(NULL != node3);
		CHECK(node2 == tree->root);
		//check node2 fields
		CHECK(node3 == node2->right);
		CHECK(node1 == node2->left);
		CHECK(NULL == node2->parent);
		CHECK(BLACK == node2->color);
		CHECK(53 == node2->contents);
		//check node1 fields
		CHECK(NULL == node1->left);
		CHECK(NULL == node1->right);
		CHECK(node2 == node1->parent);
		CHECK(RED == node1->color);
		CHECK(42 == node1->contents);
		//check node3 fields
		CHECK(NULL == node3->left);
		CHECK(NULL == node3->right);
		CHECK(node2 == node3->parent);
		CHECK(RED == node3->color);
		CHECK(99 == node3->contents);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_rb_insert_parent_uncle_mismatch_inside_left){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42);
		rb_node_t* node2 = rb_tree_insert(tree, 20);
		CHECK(node1 == tree->root);
		CHECK(node2 == tree->root->left);
		CHECK(NULL == tree->root->right);
		CHECK(RED == node2->color);
		rb_node_t* node3 = rb_tree_insert(tree, 33);
		CHECK(NULL != node3);
		CHECK(node3 == tree->root);
		//check node3 fields
		CHECK(node2 == node3->left);
		CHECK(node1 == node3->right);
		CHECK(NULL == node3->parent);
		CHECK(BLACK == node3->color);
		CHECK(33 == node3->contents);
		//check node2 fields
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(node3 == node2->parent);
		CHECK(RED == node2->color);
		CHECK(20 == node2->contents);
		//check node1 fields
		CHECK(NULL == node1->left);
		CHECK(NULL == node1->right);
		CHECK(node3 == node1->parent);
		CHECK(RED == node1->color);
		CHECK(42 == node1->contents);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	TEST(Verify_rb_insert_parent_uncle_mismatch_inside_right){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42);
		rb_node_t* node2 = rb_tree_insert(tree, 99);
		CHECK(node1 == tree->root);
		CHECK(node2 == tree->root->right);
		CHECK(NULL == tree->root->left);
		CHECK(RED == node2->color);
		rb_node_t* node3 = rb_tree_insert(tree, 88);
		CHECK(NULL != node3);
		CHECK(node3 == tree->root);
		//check node3 fields
		CHECK(node1 == node3->left);
		CHECK(node2 == node3->right);
		CHECK(NULL == node3->parent);
		CHECK(BLACK == node3->color);
		CHECK(88 == node3->contents);
		//check node2 fields
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(node3 == node2->parent);
		CHECK(RED == node2->color);
		CHECK(99 == node2->contents);
		//check node1 fields
		CHECK(NULL == node1->left);
		CHECK(NULL == node1->right);
		CHECK(node3 == node1->parent);
		CHECK(RED == node1->color);
		CHECK(42 == node1->contents);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(tree);
	}
	
	//-------------------------------------------------------------------------
	// Test lookup function
	//-------------------------------------------------------------------------
	TEST(Verify_rb_lookup_returns_null_if_not_found){
		rb_tree_t* tree = rb_tree_new();
		rb_tree_insert(tree, 42);
		rb_tree_insert(tree, 33);
		rb_tree_insert(tree, 88);
		rb_tree_insert(tree, 15);
		CHECK(NULL == rb_tree_lookup(tree, 78));
		mem_release(tree);
	}
	TEST(Verify_rb_lookup_returns_correct_node){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42);
		rb_node_t* node2 = rb_tree_insert(tree, 33);
		rb_node_t* node3 = rb_tree_insert(tree, 88);
		rb_node_t* node4 = rb_tree_insert(tree, 15);
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->left);
		CHECK(node3 == node1->right);
		CHECK(node4 == node2->left);
		CHECK(42 == node1->contents);
		CHECK(33 == node2->contents);
		CHECK(88 == node3->contents);
		CHECK(15 == node4->contents);
		CHECK(node1 == rb_tree_lookup(tree, 42));
		CHECK(node2 == rb_tree_lookup(tree, 33));
		CHECK(node3 == rb_tree_lookup(tree, 88));
		CHECK(node4 == rb_tree_lookup(tree, 15));
		mem_release(tree);
	}

	//-------------------------------------------------------------------------
	// Test delete function
	//-------------------------------------------------------------------------
	//first class: delete nodes that have at most one non-null child
	//case 1; red node: only leaf children
	//properties of rbt prevent red node w/ only one non-leaf black child.
	//node w/ two non-leaf black children handled by second class.
	TEST(Verify_rb_delete_red_node_without_children){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42);
		rb_node_t* node2 = rb_tree_insert(tree, 33);
		rb_node_t* node3 = rb_tree_insert(tree, 88);
		rb_node_t* node4 = rb_tree_insert(tree, 15);
		mem_retain(node4);
		//delete node 4
		rb_tree_delete(tree, 15);
		CHECK(1 == mem_num_references(node4));
		//check node4 no longer in tree
		CHECK(NULL == node2->left);
		CHECK(node2 == node1->left);
		CHECK(node3 == node1->right)
		CHECK(node1 == tree->root);
		CHECK(BLACK == node1->color);
		CHECK(BLACK == node2->color);
		CHECK(BLACK == node3->color);
		//check node4 pointers are nulld
		CHECK(NULL == node4->parent);
		CHECK(NULL == node4->left);
		CHECK(NULL == node4->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node4);
		mem_release(tree);
	}
	//case 2: black node, one red child
	TEST(Verify_rb_delete_left_black_node_with_single_red_left_child){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42);
		rb_node_t* node2 = rb_tree_insert(tree, 33);
		rb_node_t* node3 = rb_tree_insert(tree, 88);
		rb_node_t* node4 = rb_tree_insert(tree, 15);
		mem_retain(node2);
		//delete node 2
		rb_tree_delete(tree, 33);
		CHECK(1 == mem_num_references(node2));
		CHECK(node1 == tree->root);
		CHECK(node4 == node1->left);
		CHECK(node3 == node1->right);
		CHECK(NULL == node4->left);
		CHECK(NULL == node4->right);
		CHECK(node1 == node4->parent);
		CHECK(BLACK == node1->color);
		CHECK(BLACK == node3->color);
		CHECK(BLACK == node4->color);
		//check node2 pointers are nulld
		CHECK(NULL == node2->parent);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node2);
		mem_release(tree);
	}
	TEST(Verify_rb_delete_left_black_node_with_single_red_right_child){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42);
		rb_node_t* node2 = rb_tree_insert(tree, 33);
		rb_node_t* node3 = rb_tree_insert(tree, 88);
		rb_node_t* node4 = rb_tree_insert(tree, 38);
		mem_retain(node2);
		//delete node 2
		rb_tree_delete(tree, 33);
		CHECK(1 == mem_num_references(node2));
		CHECK(node1 == tree->root);
		CHECK(node4 == node1->left);
		CHECK(node3 == node1->right);
		CHECK(NULL == node4->left);
		CHECK(NULL == node4->right);
		CHECK(node1 == node4->parent);
		CHECK(BLACK == node1->color);
		CHECK(BLACK == node3->color);
		CHECK(BLACK == node4->color);
		//check node2 pointers are nulld
		CHECK(NULL == node2->parent);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node2);
		mem_release(tree);
	}
	TEST(Verify_rb_delete_right_black_node_with_single_red_right_child){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42);
		rb_node_t* node2 = rb_tree_insert(tree, 33);
		rb_node_t* node3 = rb_tree_insert(tree, 88);
		rb_node_t* node4 = rb_tree_insert(tree, 98);
		mem_retain(node3);
		//delete node 3
		rb_tree_delete(tree, 88);
		CHECK(1 == mem_num_references(node3));
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->left);
		CHECK(node4 == node1->right);
		CHECK(NULL == node4->left);
		CHECK(NULL == node4->right);
		CHECK(node1 == node4->parent);
		CHECK(BLACK == node1->color);
		CHECK(BLACK == node2->color);
		CHECK(BLACK == node4->color);
		//check node3 pointers are nulld
		CHECK(NULL == node3->parent);
		CHECK(NULL == node3->left);
		CHECK(NULL == node3->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node3);
		mem_release(tree);
	}
	TEST(Verify_rb_delete_right_black_node_with_single_red_left_child){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42);
		rb_node_t* node2 = rb_tree_insert(tree, 33);
		rb_node_t* node3 = rb_tree_insert(tree, 88);
		rb_node_t* node4 = rb_tree_insert(tree, 68);
		mem_retain(node3);
		//delete node 3
		rb_tree_delete(tree, 88);
		CHECK(1 == mem_num_references(node3));
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->left);
		CHECK(node4 == node1->right);
		CHECK(NULL == node4->left);
		CHECK(NULL == node4->right);
		CHECK(node1 == node4->parent);
		CHECK(BLACK == node1->color);
		CHECK(BLACK == node2->color);
		CHECK(BLACK == node4->color);
		//check node3 pointers are nulld
		CHECK(NULL == node3->parent);
		CHECK(NULL == node3->left);
		CHECK(NULL == node3->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node3);
		mem_release(tree);
	}
	//case 3: black node, no non-null children, red parent
	//red parent implies non-null black sibbling
	//four subcases for sibbling's children
	//3.1: sibbling has no children
	//3.1.1: test when node being deleted is parent->right and parent is grandparent->right
	TEST(Verify_rb_delete_black_node_from_red_parent_sib_no_children_right){
		int target = 99;
		//create tree w/ several nodes
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42); //root
		rb_node_t* node2 = rb_tree_insert(tree, 22); //untouched
		rb_node_t* node3 = rb_tree_insert(tree, 88); //parent
		rb_node_t* node4 = rb_tree_insert(tree, 77); //sibbling
		rb_node_t* node5 = rb_tree_insert(tree, target); //target
		//force colors to match scenario we're testing
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		//confirm tree is valid & node can be found
		CHECK(OK == rb_tree_is_valid(tree));
		CHECK(node5 == rb_tree_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->right);
		CHECK(node4 == node3->left);
		CHECK(node5 == node3->right);
		//delete the node from the tree
		mem_retain(node5);
		rb_tree_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rb_tree_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//3.1.2: test when node being deleted is parent->left and parent is grandparent->left
	TEST(Verify_rb_delete_black_node_from_red_parent_sib_no_children_left){
		int target = 15;
		//create tree w/ several nodes
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 88); //root
		rb_node_t* node2 = rb_tree_insert(tree, 99); //untouched
		rb_node_t* node3 = rb_tree_insert(tree, 42); //parent
		rb_node_t* node4 = rb_tree_insert(tree, 55); //sibbling
		rb_node_t* node5 = rb_tree_insert(tree, target); //target
		//force colors to match scenario we're testing
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		//confirm tree is valid & node can be found
		CHECK(OK == rb_tree_is_valid(tree));
		CHECK(node5 == rb_tree_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->left);
		CHECK(node4 == node3->right);
		CHECK(node5 == node3->left);
		//delete the node from the tree
		mem_retain(node5);
		rb_tree_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rb_tree_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//3.2: sibbling has outside child
	//3.2.1: test when node being deleted is parent->right and parent is grandparent->right
	TEST(Verify_rb_delete_black_node_from_red_parent_sib_has_outside_child_right){
		int target = 99;
		//create tree w/ several nodes
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42); //root
		rb_node_t* node2 = rb_tree_insert(tree, 22); //untouched
		rb_node_t* node3 = rb_tree_insert(tree, 88); //parent
		rb_node_t* node4 = rb_tree_insert(tree, 77); //sibbling
		rb_node_t* node5 = rb_tree_insert(tree, target); //target
		rb_node_t* node6 = rb_tree_insert(tree, 70); //sib child
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		node6->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rb_tree_is_valid(tree));
		CHECK(node5 == rb_tree_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->right);
		CHECK(node4 == node3->left);
		CHECK(node5 == node3->right);
		CHECK(node6 == node4->left);
		//delete the node from the tree
		mem_retain(node5);
		rb_tree_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rb_tree_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//3.2.2: test when node being deleted is parent->left and parent is grandparent->left
	TEST(Verify_rb_delete_black_node_from_red_parent_sib_has_outside_child_left){
		int target = 12;
		//create tree w/ several nodes
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 88); //root
		rb_node_t* node2 = rb_tree_insert(tree, 99); //untouched
		rb_node_t* node3 = rb_tree_insert(tree, 42); //parent
		rb_node_t* node4 = rb_tree_insert(tree, 55); //sibbling
		rb_node_t* node5 = rb_tree_insert(tree, target); //target
		rb_node_t* node6 = rb_tree_insert(tree, 64); //sib child
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		node6->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rb_tree_is_valid(tree));
		CHECK(node5 == rb_tree_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->left);
		CHECK(node4 == node3->right);
		CHECK(node5 == node3->left);
		CHECK(node6 == node4->right);
		//delete the node from the tree
		mem_retain(node5);
		rb_tree_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rb_tree_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//3.3: sibbling has inside child
	//3.3.1: test when node being deleted is parent->right and parent is grandparent->right
	TEST(Verify_rb_delete_black_node_from_red_parent_sib_has_inside_child_right){
		int target = 99;
		//create tree w/ several nodes
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42); //root
		rb_node_t* node2 = rb_tree_insert(tree, 22); //untouched
		rb_node_t* node3 = rb_tree_insert(tree, 88); //parent
		rb_node_t* node4 = rb_tree_insert(tree, 70); //sibbling
		rb_node_t* node5 = rb_tree_insert(tree, target); //target
		rb_node_t* node6 = rb_tree_insert(tree, 78); //sib child
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		node6->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rb_tree_is_valid(tree));
		CHECK(node5 == rb_tree_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->right);
		CHECK(node4 == node3->left);
		CHECK(node5 == node3->right);
		CHECK(node6 == node4->right);
		//delete the node from the tree
		mem_retain(node5);
		rb_tree_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rb_tree_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//3.3.2: test when node being deleted is parent->left and parent is grandparent->left
	TEST(Verify_rb_delete_black_node_from_red_parent_sib_has_inside_child_left){
		int target = 15;
		//create tree w/ several nodes
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 88); //root
		rb_node_t* node2 = rb_tree_insert(tree, 99); //untouched
		rb_node_t* node3 = rb_tree_insert(tree, 42); //parent
		rb_node_t* node4 = rb_tree_insert(tree, 55); //sibbling
		rb_node_t* node5 = rb_tree_insert(tree, target); //target
		rb_node_t* node6 = rb_tree_insert(tree, 48); //sib child
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		node6->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rb_tree_is_valid(tree));
		CHECK(node5 == rb_tree_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->left);
		CHECK(node4 == node3->right);
		CHECK(node5 == node3->left);
		CHECK(node6 == node4->left);
		//delete the node from the tree
		mem_retain(node5);
		rb_tree_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rb_tree_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//3.4: sibbling has no children
	//3.4.1: test when node being deleted is parent->right and parent is grandparent->right
	TEST(Verify_rb_delete_black_node_from_red_parent_sib_has_two_children_right){
		int target = 99;
		//create tree w/ several nodes
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42); //root
		rb_node_t* node2 = rb_tree_insert(tree, 22); //untouched
		rb_node_t* node3 = rb_tree_insert(tree, 88); //parent
		rb_node_t* node4 = rb_tree_insert(tree, 70); //sibbling
		rb_node_t* node5 = rb_tree_insert(tree, target); //target
		rb_node_t* node6 = rb_tree_insert(tree, 78); //sib child 1
		rb_node_t* node7 = rb_tree_insert(tree, 64); //sib child 2
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		node6->color = RED;
		node7->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rb_tree_is_valid(tree));
		CHECK(node5 == rb_tree_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->right);
		CHECK(node4 == node3->left);
		CHECK(node5 == node3->right);
		CHECK(node6 == node4->right);
		CHECK(node7 == node4->left);
		//delete the node from the tree
		mem_retain(node5);
		rb_tree_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rb_tree_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//3.4.2: test when node being deleted is parent->left and parent is grandparent->left
	TEST(Verify_rb_delete_black_node_from_red_parent_sib_has_two_children_left){
		int target = 15;
		//create tree w/ several nodes
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 88); //root
		rb_node_t* node2 = rb_tree_insert(tree, 99); //untouched
		rb_node_t* node3 = rb_tree_insert(tree, 42); //parent
		rb_node_t* node4 = rb_tree_insert(tree, 55); //sibbling
		rb_node_t* node5 = rb_tree_insert(tree, target); //target
		rb_node_t* node6 = rb_tree_insert(tree, 48); //sib child 1
		rb_node_t* node7 = rb_tree_insert(tree, 64); //sib child 2
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		node6->color = RED;
		node7->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rb_tree_is_valid(tree));
		CHECK(node5 == rb_tree_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->left);
		CHECK(node4 == node3->right);
		CHECK(node5 == node3->left);
		CHECK(node6 == node4->left);
		CHECK(node7 == node4->right);
		//delete the node from the tree
		mem_retain(node5);
		rb_tree_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rb_tree_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//case 4: black node, no non-null children, black parent
	//properties of RBT imply node has a sibbling
	//five subcases
	//4.1: sibbling is black, no children //TODO
	//4.2: sibbling is black, left red child
	//4.3: sibbling is black, right red child
	//4.4: sibbling is black, two red children
	//4.5: sibbling is red, two black children
	//second class: deleting nodes that have two children
	//third class: special cases: deleting root
	TEST(Verify_rb_delete_root_node_with_single_red_left_child){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 88);
		rb_node_t* node2 = rb_tree_insert(tree, 42);
		mem_retain(node1);
		rb_tree_delete(tree, 88);
		CHECK(1 == mem_num_references(node1));
		CHECK(node2 == tree->root);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(NULL == node2->parent);
		//check node1 pointers are nulld
		CHECK(NULL == node1->parent);
		CHECK(NULL == node1->left);
		CHECK(NULL == node1->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node1);
		mem_release(tree);
	}
	TEST(Verify_rb_delete_root_node_with_single_red_right_child){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 42);
		rb_node_t* node2 = rb_tree_insert(tree, 88);
		mem_retain(node1);
		rb_tree_delete(tree, 42);
		CHECK(1 == mem_num_references(node1));
		CHECK(node2 == tree->root);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(NULL == node2->parent);
		//check node1 pointers are nulld
		CHECK(NULL == node1->parent);
		CHECK(NULL == node1->left);
		CHECK(NULL == node1->right);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node1);
		mem_release(tree);
	}
	TEST(Verify_rb_delete_root_node_with_no_children){
		rb_tree_t* tree = rb_tree_new();
		rb_node_t* node1 = rb_tree_insert(tree, 88);
		mem_retain(node1);
		rb_tree_delete(tree, 88);
		CHECK(1 == mem_num_references(node1));
		CHECK(NULL == tree->root);
		CHECK(NULL == node1->left);
		CHECK(NULL == node1->right);
		CHECK(NULL == node1->parent);
		CHECK(OK == rb_tree_is_valid(tree));
		mem_release(node1);
		mem_release(tree);
	}
}

