// Unit Test Framework Includes
#include "test.h"

#include "rbt.h"
#include "mem.h"

static int test_compare(void* a, void* b){
	int ia = (int)(mem_unbox(a));
	int ib = (int)(mem_unbox(b));
	return (ia<ib ? -1 : (ib>ia ? 1 : 0));
}

static void test_setup(void) { }
//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
TEST_SUITE(RB) {
	//-------------------------------------------------------------------------
	// Test the rbt_node_new function
	//-------------------------------------------------------------------------
	TEST(Verify_rbt_node_new_returns_a_new_node){
		void* box42 = mem_box(42);
		rbt_node_t* node = rbt_node_new(box42);
		CHECK(NULL != node);
		CHECK(NULL == node->left);
		CHECK(NULL == node->right);
		CHECK(NULL == node->parent);
		CHECK(box42 == node->contents);
		//CHECK(OK == rbt_check_node(node, -1, -1)); //TODO: fix this?
		mem_release(node);
	}

	//-------------------------------------------------------------------------
	// Test the rbt_new function
	//-------------------------------------------------------------------------
	TEST(Verify_rbt_new_returns_an_empty_red_black_tree){
		rbt_t* tree = rbt_new(test_compare);
		CHECK(NULL != tree);
		CHECK(NULL == tree->root);
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}

	//-------------------------------------------------------------------------
	// Test the test function. testception.
	//-------------------------------------------------------------------------
	TEST(Verify_null_and_empty_trees_are_considered_valid){
		rbt_t* tree = NULL;
		CHECK(OK == rbt_check_status(tree));
		tree = rbt_new(test_compare);
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_checks_root_is_always_black_property){
		rbt_t* tree = rbt_new(test_compare);
		void* box88 = mem_box(88);
		rbt_insert(tree, box88);
		CHECK(BLACK == tree->root->color);
		CHECK(OK == rbt_check_status(tree));
		tree->root->color = RED;
		CHECK(BAD_ROOT_COLOR == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_nodes_not_sorted_two_nodes){
		rbt_t* tree = rbt_new(test_compare);
		void* box42 = mem_box(42);
		rbt_node_t* node1 = rbt_node_new(box42);
		void* box88 = mem_box(88);
		rbt_node_t* node2 = rbt_node_new(box88);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = NULL;
		node1->left = node2;
		node1->right = NULL;
		node2->color = RED;
		node2->parent = node1;
		node2->left = NULL;
		node2->right = NULL;
		CHECK(OUT_OF_ORDER == rbt_check_status(tree));
		mem_release(tree);
	}
	/*
	TEST(Verify_tree_is_valid_fails_when_nodes_not_sorted_four_nodes){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_node_new(42);
		rbt_node_t* node2 = rbt_node_new(88);
		rbt_node_t* node3 = rbt_node_new(25);
		rbt_node_t* node4 = rbt_node_new(99);
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
		CHECK(OUT_OF_ORDER == rbt_check_status(tree));
		node2->left = NULL;
		node2->right = node4;
		CHECK(OK == rbt_check_status(tree));
		node1->left = node2;
		node1->right = node3;
		CHECK(OUT_OF_ORDER == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_black_nodes_are_unbalanced_two_nodes){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_node_new(42);
		rbt_node_t* node2 = rbt_node_new(88);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = NULL;
		node1->left = NULL;
		node1->right = node2;
		node2->color = BLACK;
		node2->parent = node1;
		node2->left = NULL;
		node2->right = NULL;
		CHECK(BLACK_NODES_UNBALANCED == rbt_check_status(tree));
		node2->color = RED;
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_black_nodes_are_unbalanced_three_nodes){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_node_new(42);
		rbt_node_t* node2 = rbt_node_new(22);
		rbt_node_t* node3 = rbt_node_new(88);
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
		CHECK(BLACK_NODES_UNBALANCED == rbt_check_status(tree));
		node2->color = BLACK;
		node3->color = RED;
		CHECK(BLACK_NODES_UNBALANCED == rbt_check_status(tree));
		node2->color = BLACK;
		node3->color = BLACK;
		CHECK(OK == rbt_check_status(tree));
		node2->color = RED;
		node3->color = RED;
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_black_nodes_are_unbalanced_four_nodes){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_node_new(42);
		rbt_node_t* node2 = rbt_node_new(22);
		rbt_node_t* node3 = rbt_node_new(88);
		rbt_node_t* node4 = rbt_node_new(33);
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
		CHECK(BLACK_NODES_UNBALANCED == rbt_check_status(tree));
		node2->color = BLACK;
		node3->color = RED;
		CHECK(BLACK_NODES_UNBALANCED == rbt_check_status(tree));
		node4->color = RED;
		CHECK(BLACK_NODES_UNBALANCED == rbt_check_status(tree));
		node2->color = BLACK;
		node3->color = BLACK;
		node4->color = BLACK;
		CHECK(BLACK_NODES_UNBALANCED == rbt_check_status(tree));
		node4->color = RED;
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_node_is_unvalid_color){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_node_new(42);
		rbt_node_t* node2 = rbt_node_new(88);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = NULL;
		node1->right = node2;
		node1->left = NULL;
		node2->color = 42;
		node2->parent = node1;
		node2->right = NULL;
		node2->left = NULL;
		CHECK(UNKNOWN_COLOR == rbt_check_status(tree));
		node2->color = RED;
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_root_parent_pointer_is_not_null){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_node_new(42);
		rbt_node_t* node2 = rbt_node_new(88);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = node2;
		node1->left = NULL;
		node1->right = node2;
		node2->color = RED;
		node2->parent = node1;
		node2->left = NULL;
		node2->right = NULL;
		CHECK(BAD_PARENT_POINTER == rbt_check_status(tree));
		node1->parent = NULL;
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_node_parent_poitners_are_wrong_two_nodes){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_node_new(42);
		rbt_node_t* node2 = rbt_node_new(88);
		rbt_node_t* node3 = rbt_node_new(99);
		tree->root = node1;
		node1->color = BLACK;
		node1->parent = NULL;
		node1->left = NULL;
		node1->right = node2;
		node2->color = RED;
		node2->parent = node1;
		node2->left = NULL;
		node2->right = NULL;
		CHECK(OK == rbt_check_status(tree));
		node2->parent = node3;
		CHECK(BAD_PARENT_POINTER == rbt_check_status(tree));
		node2->parent = NULL;
		CHECK(BAD_PARENT_POINTER == rbt_check_status(tree));
		node2->parent = node1;
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
		mem_release(node3);
	}
	TEST(Verify_tree_is_valid_fails_when_node_parent_poitners_are_wrong_four_nodes){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_node_new(42);
		rbt_node_t* node2 = rbt_node_new(22);
		rbt_node_t* node3 = rbt_node_new(88);
		rbt_node_t* node4 = rbt_node_new(33);
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
		CHECK(OK == rbt_check_status(tree));
		node4->parent = node1;
		CHECK(BAD_PARENT_POINTER == rbt_check_status(tree));
		node4->parent = NULL;
		CHECK(BAD_PARENT_POINTER == rbt_check_status(tree));
		node4->parent = node4;
		CHECK(BAD_PARENT_POINTER == rbt_check_status(tree));
		node4->parent = node2;
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_tree_is_valid_fails_when_node_points_to_itself){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_node_new(42);
		rbt_node_t* node2 = rbt_node_new(22);
		rbt_node_t* node3 = rbt_node_new(88);
		rbt_node_t* node4 = rbt_node_new(33);
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
		CHECK(OK == rbt_check_status(tree));
		node4->right = node4;
		CHECK(SELF_REFERENCE == rbt_check_status(tree));
		node4->right = NULL;
		node2->left = node2;
		CHECK(SELF_REFERENCE == rbt_check_status(tree));
		node2->left = NULL;
		node2->right = node2;
		CHECK(SELF_REFERENCE == rbt_check_status(tree));
		node2->right = node4;
		node3->left = node3;
		CHECK(SELF_REFERENCE == rbt_check_status(tree));
		node3->left = NULL;
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}

	//-------------------------------------------------------------------------
	// Test insert functions
	//-------------------------------------------------------------------------
	TEST(Verify_rbt_insert_to_an_empty_list_assigns_root){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node = rbt_insert(tree, 42);
		CHECK(NULL != node);
		CHECK(tree->root == node);
		CHECK(42 == node->contents);
		CHECK(NULL == node->left);
		CHECK(NULL == node->right);
		CHECK(NULL == node->parent);
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_rbt_insert_node_to_root_left_works){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* root = rbt_insert(tree, 42);
		rbt_node_t* node1 = rbt_insert(tree, 31);
		CHECK(NULL != root);
		CHECK(NULL != node1);
		CHECK(tree->root == root);
		CHECK(root == node1->parent);
		CHECK(31 == node1->contents);
		CHECK(node1 == root->left);
		CHECK(NULL == root->right);
		CHECK(RED == node1->color);
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_rbt_insert_node_to_root_right_works){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* root = rbt_insert(tree, 42);
		rbt_node_t* node2 = rbt_insert(tree, 64);
		CHECK(NULL != root);
		CHECK(NULL != node2);
		CHECK(tree->root == root);
		CHECK(root == node2->parent);
		CHECK(64 == node2->contents);
		CHECK(node2 == root->right);
		CHECK(NULL == root->left);
		CHECK(RED == node2->color);
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_rbt_insert_first_level_works){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* root = rbt_insert(tree, 42);
		rbt_node_t* node1 = rbt_insert(tree, 31);
		rbt_node_t* node2 = rbt_insert(tree, 64);
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
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_rbt_insert_below_full_first_level_works){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* root = rbt_insert(tree, 42);
		rbt_node_t* node1 = rbt_insert(tree, 31);
		rbt_node_t* node2 = rbt_insert(tree, 64);
		rbt_node_t* node3 = rbt_insert(tree, 15);
		CHECK(NULL != node3);
		CHECK(15 == node3->contents);
		CHECK(node1->left == node3);
		CHECK(NULL == node3->left);
		CHECK(NULL == node3->right);
		CHECK(BLACK == root->color);
		CHECK(BLACK == node1->color);
		CHECK(BLACK == node2->color);
		CHECK(RED == node3->color);
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_rbt_insert_parent_uncle_mismatch_outside_left){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42);
		rbt_node_t* node2 = rbt_insert(tree, 32);
		CHECK(node1 == tree->root);
		CHECK(node2 == tree->root->left);
		CHECK(NULL == tree->root->right);
		CHECK(RED == node2->color);
		//tree->root->right == NULL ; black implicitly
		rbt_node_t* node3 = rbt_insert(tree, 15);
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
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_rbt_insert_parent_uncle_mismatch_outside_right){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42);
		rbt_node_t* node2 = rbt_insert(tree, 53);
		CHECK(node1 == tree->root);
		CHECK(node2 == tree->root->right);
		CHECK(NULL == tree->root->left);
		CHECK(RED == node2->color);
		rbt_node_t* node3 = rbt_insert(tree, 99);
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
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_rbt_insert_parent_uncle_mismatch_inside_left){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42);
		rbt_node_t* node2 = rbt_insert(tree, 20);
		CHECK(node1 == tree->root);
		CHECK(node2 == tree->root->left);
		CHECK(NULL == tree->root->right);
		CHECK(RED == node2->color);
		rbt_node_t* node3 = rbt_insert(tree, 33);
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
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	TEST(Verify_rbt_insert_parent_uncle_mismatch_inside_right){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42);
		rbt_node_t* node2 = rbt_insert(tree, 99);
		CHECK(node1 == tree->root);
		CHECK(node2 == tree->root->right);
		CHECK(NULL == tree->root->left);
		CHECK(RED == node2->color);
		rbt_node_t* node3 = rbt_insert(tree, 88);
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
		CHECK(OK == rbt_check_status(tree));
		mem_release(tree);
	}
	
	//-------------------------------------------------------------------------
	// Test lookup function
	//-------------------------------------------------------------------------
	TEST(Verify_rbt_lookup_returns_null_if_not_found){
		rbt_t* tree = rbt_new(test_compare);
		rbt_insert(tree, 42);
		rbt_insert(tree, 33);
		rbt_insert(tree, 88);
		rbt_insert(tree, 15);
		CHECK(NULL == rbt_lookup(tree, 78));
		mem_release(tree);
	}
	TEST(Verify_rbt_lookup_returns_correct_node){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42);
		rbt_node_t* node2 = rbt_insert(tree, 33);
		rbt_node_t* node3 = rbt_insert(tree, 88);
		rbt_node_t* node4 = rbt_insert(tree, 15);
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->left);
		CHECK(node3 == node1->right);
		CHECK(node4 == node2->left);
		CHECK(42 == node1->contents);
		CHECK(33 == node2->contents);
		CHECK(88 == node3->contents);
		CHECK(15 == node4->contents);
		CHECK(node1 == rbt_lookup(tree, 42));
		CHECK(node2 == rbt_lookup(tree, 33));
		CHECK(node3 == rbt_lookup(tree, 88));
		CHECK(node4 == rbt_lookup(tree, 15));
		mem_release(tree);
	}

	//-------------------------------------------------------------------------
	// Test delete function
	//-------------------------------------------------------------------------
	//first class: delete nodes that have at most one non-null child
	//case 1; red node: only leaf children
	//properties of rbt prevent red node w/ only one non-leaf black child.
	//node w/ two non-leaf black children handled by second class.
	TEST(Verify_rbt_delete_red_node_without_children){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42);
		rbt_node_t* node2 = rbt_insert(tree, 33);
		rbt_node_t* node3 = rbt_insert(tree, 88);
		rbt_node_t* node4 = rbt_insert(tree, 15);
		mem_retain(node4);
		//delete node 4
		rbt_delete(tree, 15);
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
		CHECK(OK == rbt_check_status(tree));
		mem_release(node4);
		mem_release(tree);
	}
	//case 2: black node, one red child
	TEST(Verify_rbt_delete_left_black_node_with_single_red_left_child){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42);
		rbt_node_t* node2 = rbt_insert(tree, 33);
		rbt_node_t* node3 = rbt_insert(tree, 88);
		rbt_node_t* node4 = rbt_insert(tree, 15);
		mem_retain(node2);
		//delete node 2
		rbt_delete(tree, 33);
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
		CHECK(OK == rbt_check_status(tree));
		mem_release(node2);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_left_black_node_with_single_red_right_child){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42);
		rbt_node_t* node2 = rbt_insert(tree, 33);
		rbt_node_t* node3 = rbt_insert(tree, 88);
		rbt_node_t* node4 = rbt_insert(tree, 38);
		mem_retain(node2);
		//delete node 2
		rbt_delete(tree, 33);
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
		CHECK(OK == rbt_check_status(tree));
		mem_release(node2);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_right_black_node_with_single_red_right_child){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42);
		rbt_node_t* node2 = rbt_insert(tree, 33);
		rbt_node_t* node3 = rbt_insert(tree, 88);
		rbt_node_t* node4 = rbt_insert(tree, 98);
		mem_retain(node3);
		//delete node 3
		rbt_delete(tree, 88);
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
		CHECK(OK == rbt_check_status(tree));
		mem_release(node3);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_right_black_node_with_single_red_left_child){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42);
		rbt_node_t* node2 = rbt_insert(tree, 33);
		rbt_node_t* node3 = rbt_insert(tree, 88);
		rbt_node_t* node4 = rbt_insert(tree, 68);
		mem_retain(node3);
		//delete node 3
		rbt_delete(tree, 88);
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
		CHECK(OK == rbt_check_status(tree));
		mem_release(node3);
		mem_release(tree);
	}
	//case 3: black node, no non-null children, red parent
	//red parent implies non-null black sibbling
	//four subcases for sibbling's children
	//3.1: sibbling has no children
	//3.1.1: test when node being deleted is parent->right and parent is grandparent->right
	TEST(Verify_rbt_delete_black_node_from_red_parent_sib_no_children_right){
		int target = 99;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42); //root
		rbt_node_t* node2 = rbt_insert(tree, 22); //untouched
		rbt_node_t* node3 = rbt_insert(tree, 88); //parent
		rbt_node_t* node4 = rbt_insert(tree, 77); //sibbling
		rbt_node_t* node5 = rbt_insert(tree, target); //target
		//force colors to match scenario we're testing
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node5 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->right);
		CHECK(node4 == node3->left);
		CHECK(node5 == node3->right);
		//delete the node from the tree
		mem_retain(node5);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//3.1.2: test when node being deleted is parent->left and parent is grandparent->left
	TEST(Verify_rbt_delete_black_node_from_red_parent_sib_no_children_left){
		int target = 15;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 88); //root
		rbt_node_t* node2 = rbt_insert(tree, 99); //untouched
		rbt_node_t* node3 = rbt_insert(tree, 42); //parent
		rbt_node_t* node4 = rbt_insert(tree, 55); //sibbling
		rbt_node_t* node5 = rbt_insert(tree, target); //target
		//force colors to match scenario we're testing
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node5 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->left);
		CHECK(node4 == node3->right);
		CHECK(node5 == node3->left);
		//delete the node from the tree
		mem_retain(node5);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//3.2: sibbling has outside child
	//3.2.1: test when node being deleted is parent->right and parent is grandparent->right
	TEST(Verify_rbt_delete_black_node_from_red_parent_sib_has_outside_child_right){
		int target = 99;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42); //root
		rbt_node_t* node2 = rbt_insert(tree, 22); //untouched
		rbt_node_t* node3 = rbt_insert(tree, 88); //parent
		rbt_node_t* node4 = rbt_insert(tree, 77); //sibbling
		rbt_node_t* node5 = rbt_insert(tree, target); //target
		rbt_node_t* node6 = rbt_insert(tree, 70); //sib child
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		node6->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node5 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->right);
		CHECK(node4 == node3->left);
		CHECK(node5 == node3->right);
		CHECK(node6 == node4->left);
		//delete the node from the tree
		mem_retain(node5);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//3.2.2: test when node being deleted is parent->left and parent is grandparent->left
	TEST(Verify_rbt_delete_black_node_from_red_parent_sib_has_outside_child_left){
		int target = 12;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 88); //root
		rbt_node_t* node2 = rbt_insert(tree, 99); //untouched
		rbt_node_t* node3 = rbt_insert(tree, 42); //parent
		rbt_node_t* node4 = rbt_insert(tree, 55); //sibbling
		rbt_node_t* node5 = rbt_insert(tree, target); //target
		rbt_node_t* node6 = rbt_insert(tree, 64); //sib child
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		node6->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node5 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->left);
		CHECK(node4 == node3->right);
		CHECK(node5 == node3->left);
		CHECK(node6 == node4->right);
		//delete the node from the tree
		mem_retain(node5);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//3.3: sibbling has inside child
	//3.3.1: test when node being deleted is parent->right and parent is grandparent->right
	TEST(Verify_rbt_delete_black_node_from_red_parent_sib_has_inside_child_right){
		int target = 99;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42); //root
		rbt_node_t* node2 = rbt_insert(tree, 22); //untouched
		rbt_node_t* node3 = rbt_insert(tree, 88); //parent
		rbt_node_t* node4 = rbt_insert(tree, 70); //sibbling
		rbt_node_t* node5 = rbt_insert(tree, target); //target
		rbt_node_t* node6 = rbt_insert(tree, 78); //sib child
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		node6->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node5 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->right);
		CHECK(node4 == node3->left);
		CHECK(node5 == node3->right);
		CHECK(node6 == node4->right);
		//delete the node from the tree
		mem_retain(node5);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//3.3.2: test when node being deleted is parent->left and parent is grandparent->left
	TEST(Verify_rbt_delete_black_node_from_red_parent_sib_has_inside_child_left){
		int target = 15;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 88); //root
		rbt_node_t* node2 = rbt_insert(tree, 99); //untouched
		rbt_node_t* node3 = rbt_insert(tree, 42); //parent
		rbt_node_t* node4 = rbt_insert(tree, 55); //sibbling
		rbt_node_t* node5 = rbt_insert(tree, target); //target
		rbt_node_t* node6 = rbt_insert(tree, 48); //sib child
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		node6->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node5 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->left);
		CHECK(node4 == node3->right);
		CHECK(node5 == node3->left);
		CHECK(node6 == node4->left);
		//delete the node from the tree
		mem_retain(node5);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//3.4: sibbling has no children
	//3.4.1: test when node being deleted is parent->right and parent is grandparent->right
	TEST(Verify_rbt_delete_black_node_from_red_parent_sib_has_two_children_right){
		int target = 99;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42); //root
		rbt_node_t* node2 = rbt_insert(tree, 22); //untouched
		rbt_node_t* node3 = rbt_insert(tree, 88); //parent
		rbt_node_t* node4 = rbt_insert(tree, 70); //sibbling
		rbt_node_t* node5 = rbt_insert(tree, target); //target
		rbt_node_t* node6 = rbt_insert(tree, 78); //sib child 1
		rbt_node_t* node7 = rbt_insert(tree, 64); //sib child 2
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		node6->color = RED;
		node7->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node5 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->right);
		CHECK(node4 == node3->left);
		CHECK(node5 == node3->right);
		CHECK(node6 == node4->right);
		CHECK(node7 == node4->left);
		//delete the node from the tree
		mem_retain(node5);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//3.4.2: test when node being deleted is parent->left and parent is grandparent->left
	TEST(Verify_rbt_delete_black_node_from_red_parent_sib_has_two_children_left){
		int target = 15;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 88); //root
		rbt_node_t* node2 = rbt_insert(tree, 99); //untouched
		rbt_node_t* node3 = rbt_insert(tree, 42); //parent
		rbt_node_t* node4 = rbt_insert(tree, 55); //sibbling
		rbt_node_t* node5 = rbt_insert(tree, target); //target
		rbt_node_t* node6 = rbt_insert(tree, 48); //sib child 1
		rbt_node_t* node7 = rbt_insert(tree, 64); //sib child 2
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		node6->color = RED;
		node7->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node5 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node3 == node1->left);
		CHECK(node4 == node3->right);
		CHECK(node5 == node3->left);
		CHECK(node6 == node4->left);
		CHECK(node7 == node4->right);
		//delete the node from the tree
		mem_retain(node5);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//case 4: black node, no non-null children, black parent
	//properties of RBT imply node has a sibbling
	//five subcases
	//4.1: sibbling is black, no children //TODO
	TEST(Verify_rbt_delete_black_node_from_black_parent_sib_has_no_children_right){
		int target = 99;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 88); //root
		rbt_node_t* node2 = rbt_insert(tree, target); //target
		rbt_node_t* node3 = rbt_insert(tree, 42); //sibbling
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = BLACK;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node2 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->right);
		CHECK(node3 == node1->left);
		//delete the node from the tree
		mem_retain(node2);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node2));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node2->parent);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node2);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_black_node_from_black_parent_sib_has_no_children_left){
		int target = 22;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42); //root
		rbt_node_t* node2 = rbt_insert(tree, target); //target
		rbt_node_t* node3 = rbt_insert(tree, 88); //sibbling
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = BLACK;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node2 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->left);
		CHECK(node3 == node1->right);
		//delete the node from the tree
		mem_retain(node2);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node2));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node2->parent);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node2);
		mem_release(tree);
	}
	//test tree rebalancing after remove. case 4.1 is the only rm case that requires a structural rebalancing:
	//trivial case: parent is tree->root (tested above) ; no action required
	//A: rebalance node w/ red sibbling (rotation moves to have black sibbling to fall in one of the following cases)
	TEST(Verify_rbt_delete_rebalance_red_sibbling_left){
		int target = 15;
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node01 = rbt_insert(tree, 42);
		rbt_node_t* node02 = rbt_insert(tree, 22);
		rbt_node_t* node03 = rbt_insert(tree, 70);
		rbt_node_t* node04 = rbt_insert(tree, 88);
		rbt_node_t* node05 = rbt_insert(tree, 90);
		rbt_node_t* node06 = rbt_insert(tree, 99);
		rbt_node_t* node07 = rbt_insert(tree, 89);
		rbt_node_t* node08 = rbt_insert(tree, 80);
		rbt_node_t* node09 = rbt_insert(tree, 60);
		rbt_node_t* node10 = rbt_insert(tree, 33);
		rbt_node_t* node11 = rbt_insert(tree, target);
		//force colors to match scenario being tested
		//note, expecting a rotation after inserting node5
		(void)node01;
		node02->color = BLACK;
		node03->color = BLACK;
		node04->color = RED;
		node05->color = BLACK;
		node06->color = BLACK;
		node07->color = BLACK;
		node08->color = BLACK;
		node09->color = BLACK;
		node10->color = BLACK;
		node11->color = BLACK;
		CHECK(OK == rbt_check_status(tree));
		CHECK(node11 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node01 == tree->root);
		CHECK(node02 == node01->left);
		CHECK(node04 == node01->right);
		CHECK(node11 == node02->left);
		CHECK(node10 == node02->right);
		CHECK(node03 == node04->left);
		CHECK(node05 == node04->right);
		CHECK(node09 == node03->left);
		CHECK(node08 == node03->right);
		CHECK(node07 == node05->left);
		CHECK(node06 == node05->right);
		//delete the node from the tree
		mem_retain(node11);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node11));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node11->parent);
		CHECK(NULL == node11->left);
		CHECK(NULL == node11->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node11);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_rebalance_red_sibbling_right){
		int target = 88;
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node01 = rbt_insert(tree, 42);
		rbt_node_t* node02 = rbt_insert(tree, 66);
		rbt_node_t* node03 = rbt_insert(tree, 22);
		rbt_node_t* node04 = rbt_insert(tree, 18);
		rbt_node_t* node05 = rbt_insert(tree, 15);
		rbt_node_t* node06 = rbt_insert(tree, target);
		rbt_node_t* node07 = rbt_insert(tree, 54);
		rbt_node_t* node08 = rbt_insert(tree, 33);
		rbt_node_t* node09 = rbt_insert(tree, 20);
		rbt_node_t* node10 = rbt_insert(tree, 16);
		rbt_node_t* node11 = rbt_insert(tree, 11);
		//force colors to match scenario being tested
		//note, expecting a rotation after inserting node5
		(void)node01;
		node02->color = BLACK;
		node03->color = BLACK;
		node04->color = RED;
		node05->color = BLACK;
		node06->color = BLACK;
		node07->color = BLACK;
		node08->color = BLACK;
		node09->color = BLACK;
		node10->color = BLACK;
		node11->color = BLACK;
		CHECK(OK == rbt_check_status(tree));
		CHECK(node06 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node01 == tree->root);
		CHECK(node04 == node01->left);
		CHECK(node02 == node01->right);
		CHECK(node07 == node02->left);
		CHECK(node06 == node02->right);
		CHECK(node05 == node04->left);
		CHECK(node03 == node04->right);
		CHECK(node09 == node03->left);
		CHECK(node08 == node03->right);
		CHECK(node11 == node05->left);
		CHECK(node10 == node05->right);
		//delete the node from the tree
		mem_retain(node06);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node06));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node06->parent);
		CHECK(NULL == node06->left);
		CHECK(NULL == node06->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node06);
		mem_release(tree);
	}
	//B: rebalance w/ black parent, black sibbling w/ black children
	TEST(Verify_rbt_delete_rebalance_black_parent_black_sib_with_black_children_left){
		int target = 15;
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42);
		rbt_node_t* node2 = rbt_insert(tree, 22);
		rbt_node_t* node3 = rbt_insert(tree, 88);
		rbt_node_t* node4 = rbt_insert(tree, 99);
		rbt_node_t* node5 = rbt_insert(tree, 75);
		rbt_node_t* node6 = rbt_insert(tree, 33);
		rbt_node_t* node7 = rbt_insert(tree, target);
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = BLACK;
		node4->color = BLACK;
		node5->color = BLACK;
		node6->color = BLACK;
		node7->color = BLACK;
		CHECK(OK == rbt_check_status(tree));
		CHECK(node7 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->left);
		CHECK(node3 == node1->right);
		CHECK(node4 == node3->right);
		CHECK(node5 == node3->left);
		CHECK(node6 == node2->right);
		CHECK(node7 == node2->left);
		//delete the node from the tree
		mem_retain(node7);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node7));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node7->parent);
		CHECK(NULL == node7->left);
		CHECK(NULL == node7->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node7);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_rebalance_black_parent_black_sib_with_black_children_right){
		int target = 75;
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42);
		rbt_node_t* node2 = rbt_insert(tree, 22);
		rbt_node_t* node3 = rbt_insert(tree, 88);
		rbt_node_t* node4 = rbt_insert(tree, 99);
		rbt_node_t* node5 = rbt_insert(tree, target);
		rbt_node_t* node6 = rbt_insert(tree, 33);
		rbt_node_t* node7 = rbt_insert(tree, 15);
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = BLACK;
		node4->color = BLACK;
		node5->color = BLACK;
		node6->color = BLACK;
		node7->color = BLACK;
		CHECK(OK == rbt_check_status(tree));
		CHECK(node5 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->left);
		CHECK(node3 == node1->right);
		CHECK(node4 == node3->right);
		CHECK(node5 == node3->left);
		CHECK(node6 == node2->right);
		CHECK(node7 == node2->left);
		//delete the node from the tree
		mem_retain(node5);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node5));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node5->parent);
		CHECK(NULL == node5->left);
		CHECK(NULL == node5->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node5);
		mem_release(tree);
	}
	//C: rebalance w/ red parent, red sibbling w/ black children
	TEST(Verify_rbt_delete_rebalance_red_parent_black_sib_with_black_children_left){
		int target = 11;
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node01 = rbt_insert(tree, 42);
		rbt_node_t* node02 = rbt_insert(tree, 66);
		rbt_node_t* node03 = rbt_insert(tree, 22);
		rbt_node_t* node04 = rbt_insert(tree, 18);
		rbt_node_t* node05 = rbt_insert(tree, 15);
		rbt_node_t* node06 = rbt_insert(tree, 88);
		rbt_node_t* node07 = rbt_insert(tree, 54);
		rbt_node_t* node08 = rbt_insert(tree, 33);
		rbt_node_t* node09 = rbt_insert(tree, 20);
		rbt_node_t* node10 = rbt_insert(tree, 16);
		rbt_node_t* node11 = rbt_insert(tree, target);
		//force colors to match scenario being tested
		//note, expecting a rotation after inserting node5
		(void)node01;
		node02->color = BLACK;
		node03->color = BLACK;
		node04->color = RED;
		node05->color = BLACK;
		node06->color = BLACK;
		node07->color = BLACK;
		node08->color = BLACK;
		node09->color = BLACK;
		node10->color = BLACK;
		node11->color = BLACK;
		CHECK(OK == rbt_check_status(tree));
		CHECK(node11 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node01 == tree->root);
		CHECK(node04 == node01->left);
		CHECK(node02 == node01->right);
		CHECK(node07 == node02->left);
		CHECK(node06 == node02->right);
		CHECK(node05 == node04->left);
		CHECK(node03 == node04->right);
		CHECK(node09 == node03->left);
		CHECK(node08 == node03->right);
		CHECK(node11 == node05->left);
		CHECK(node10 == node05->right);
		//delete the node from the tree
		mem_retain(node11);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node11));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node11->parent);
		CHECK(NULL == node11->left);
		CHECK(NULL == node11->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node11);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_rebalance_red_parent_black_sib_with_black_children_right){
		int target = 99;
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node01 = rbt_insert(tree, 42);
		rbt_node_t* node02 = rbt_insert(tree, 22);
		rbt_node_t* node03 = rbt_insert(tree, 70);
		rbt_node_t* node04 = rbt_insert(tree, 88);
		rbt_node_t* node05 = rbt_insert(tree, 90);
		rbt_node_t* node06 = rbt_insert(tree, target);
		rbt_node_t* node07 = rbt_insert(tree, 89);
		rbt_node_t* node08 = rbt_insert(tree, 80);
		rbt_node_t* node09 = rbt_insert(tree, 60);
		rbt_node_t* node10 = rbt_insert(tree, 33);
		rbt_node_t* node11 = rbt_insert(tree, 15);
		//force colors to match scenario being tested
		//note, expecting a rotation after inserting node5
		(void)node01;
		node02->color = BLACK;
		node03->color = BLACK;
		node04->color = RED;
		node05->color = BLACK;
		node06->color = BLACK;
		node07->color = BLACK;
		node08->color = BLACK;
		node09->color = BLACK;
		node10->color = BLACK;
		node11->color = BLACK;
		CHECK(OK == rbt_check_status(tree));
		CHECK(node06 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node01 == tree->root);
		CHECK(node02 == node01->left);
		CHECK(node04 == node01->right);
		CHECK(node11 == node02->left);
		CHECK(node10 == node02->right);
		CHECK(node03 == node04->left);
		CHECK(node05 == node04->right);
		CHECK(node09 == node03->left);
		CHECK(node08 == node03->right);
		CHECK(node07 == node05->left);
		CHECK(node06 == node05->right);
		//delete the node from the tree
		mem_retain(node06);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node06));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node06->parent);
		CHECK(NULL == node06->left);
		CHECK(NULL == node06->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node06);
		mem_release(tree);
	}
	//D: rebalance for sibbling w/ outside red child
	TEST(Verify_rbt_delete_rebalance_sib_with_red_child_outside_left){
		int target = 11;
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node01 = rbt_insert(tree, 42);
		rbt_node_t* node02 = rbt_insert(tree, 22);
		rbt_node_t* node03 = rbt_insert(tree, 55);
		rbt_node_t* node04 = rbt_insert(tree, 88);
		rbt_node_t* node05 = rbt_insert(tree, 90);
		rbt_node_t* node06 = rbt_insert(tree, target);
		rbt_node_t* node07 = rbt_insert(tree, 30);
		rbt_node_t* node08 = rbt_insert(tree, 89);
		rbt_node_t* node09 = rbt_insert(tree, 95);
		//force colors to match scenario being tested
		(void)node01;
		node02->color = BLACK;
		node03->color = BLACK;
		node04->color = BLACK;
		node05->color = RED;
		node06->color = BLACK;
		node07->color = BLACK;
		node08->color = BLACK;
		node09->color = BLACK;
		CHECK(OK == rbt_check_status(tree));
		CHECK(node06 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node01 == tree->root);
		CHECK(node02 == node01->left);
		CHECK(node04 == node01->right);
		CHECK(node03 == node04->left);
		CHECK(node05 == node04->right);
		CHECK(node06 == node02->left);
		CHECK(node07 == node02->right);
		CHECK(node08 == node05->left);
		CHECK(node09 == node05->right);
		//delete the node from the tree
		mem_retain(node06);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node06));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node06->parent);
		CHECK(NULL == node06->left);
		CHECK(NULL == node06->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node06);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_rebalance_sib_with_red_child_outside_right){
		int target = 88;
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node01 = rbt_insert(tree, 42);
		rbt_node_t* node02 = rbt_insert(tree, 55);
		rbt_node_t* node03 = rbt_insert(tree, 33);
		rbt_node_t* node04 = rbt_insert(tree, 22);
		rbt_node_t* node05 = rbt_insert(tree, 15);
		rbt_node_t* node06 = rbt_insert(tree, target);
		rbt_node_t* node07 = rbt_insert(tree, 50);
		rbt_node_t* node08 = rbt_insert(tree, 17);
		rbt_node_t* node09 = rbt_insert(tree, 11);
		//force colors to match scenario being tested
		(void)node01;
		node02->color = BLACK;
		node03->color = BLACK;
		node04->color = BLACK;
		node05->color = RED;
		node06->color = BLACK;
		node07->color = BLACK;
		node08->color = BLACK;
		node09->color = BLACK;
		CHECK(OK == rbt_check_status(tree));
		CHECK(node06 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node01 == tree->root);
		CHECK(node02 == node01->right);
		CHECK(node04 == node01->left);
		CHECK(node03 == node04->right);
		CHECK(node05 == node04->left);
		CHECK(node06 == node02->right);
		CHECK(node07 == node02->left);
		CHECK(node08 == node05->right);
		CHECK(node09 == node05->left);
		//delete the node from the tree
		mem_retain(node06);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node06));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node06->parent);
		CHECK(NULL == node06->left);
		CHECK(NULL == node06->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node06);
		mem_release(tree);
	}
	//E: rebalance for sibbling w/ inside red child
	TEST(Verify_rbt_delete_rebalance_sib_with_red_child_inside_left){
		int target = 11;
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node01 = rbt_insert(tree, 42);
		rbt_node_t* node02 = rbt_insert(tree, 22);
		rbt_node_t* node03 = rbt_insert(tree, 55);
		rbt_node_t* node04 = rbt_insert(tree, 88);
		rbt_node_t* node05 = rbt_insert(tree, 90);
		rbt_node_t* node06 = rbt_insert(tree, target);
		rbt_node_t* node07 = rbt_insert(tree, 30);
		rbt_node_t* node08 = rbt_insert(tree, 50);
		rbt_node_t* node09 = rbt_insert(tree, 65);
		//force colors to match scenario being tested
		(void)node01;
		node02->color = BLACK;
		node03->color = RED;
		node04->color = BLACK;
		node05->color = BLACK;
		node06->color = BLACK;
		node07->color = BLACK;
		node08->color = BLACK;
		node09->color = BLACK;
		CHECK(OK == rbt_check_status(tree));
		CHECK(node06 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node01 == tree->root);
		CHECK(node02 == node01->left);
		CHECK(node04 == node01->right);
		CHECK(node03 == node04->left);
		CHECK(node05 == node04->right);
		CHECK(node06 == node02->left);
		CHECK(node07 == node02->right);
		CHECK(node08 == node03->left);
		CHECK(node09 == node03->right);
		//delete the node from the tree
		mem_retain(node06);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node06));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node06->parent);
		CHECK(NULL == node06->left);
		CHECK(NULL == node06->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node06);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_rebalance_sib_with_red_child_inside_right){
		int target = 88;
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node01 = rbt_insert(tree, 42);
		rbt_node_t* node02 = rbt_insert(tree, 55);
		rbt_node_t* node03 = rbt_insert(tree, 33);
		rbt_node_t* node04 = rbt_insert(tree, 22);
		rbt_node_t* node05 = rbt_insert(tree, 15);
		rbt_node_t* node06 = rbt_insert(tree, target);
		rbt_node_t* node07 = rbt_insert(tree, 50);
		rbt_node_t* node08 = rbt_insert(tree, 37);
		rbt_node_t* node09 = rbt_insert(tree, 28);
		//force colors to match scenario being tested
		(void)node01;
		node02->color = BLACK;
		node03->color = RED;
		node04->color = BLACK;
		node05->color = BLACK;
		node06->color = BLACK;
		node07->color = BLACK;
		node08->color = BLACK;
		node09->color = BLACK;
		CHECK(OK == rbt_check_status(tree));
		CHECK(node06 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node01 == tree->root);
		CHECK(node02 == node01->right);
		CHECK(node04 == node01->left);
		CHECK(node03 == node04->right);
		CHECK(node05 == node04->left);
		CHECK(node06 == node02->right);
		CHECK(node07 == node02->left);
		CHECK(node08 == node03->right);
		CHECK(node09 == node03->left);
		//delete the node from the tree
		mem_retain(node06);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node06));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node06->parent);
		CHECK(NULL == node06->left);
		CHECK(NULL == node06->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node06);
		mem_release(tree);
	}
	//F: rebalance for sibbling with two red children
	TEST(Verify_rbt_delete_rebalance_sib_with_two_red_children_left){
		int target = 11;
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node01 = rbt_insert(tree, 42);
		rbt_node_t* node02 = rbt_insert(tree, 22);
		rbt_node_t* node03 = rbt_insert(tree, 55);
		rbt_node_t* node04 = rbt_insert(tree, 88);
		rbt_node_t* node05 = rbt_insert(tree, 90);
		rbt_node_t* node06 = rbt_insert(tree, target);
		rbt_node_t* node07 = rbt_insert(tree, 30);
		rbt_node_t* node08 = rbt_insert(tree, 50);
		rbt_node_t* node09 = rbt_insert(tree, 65);
		rbt_node_t* node10 = rbt_insert(tree, 89);
		rbt_node_t* node11 = rbt_insert(tree, 99);
		//force colors to match scenario being tested
		(void)node01;
		node02->color = BLACK;
		node03->color = RED;
		node04->color = BLACK;
		node05->color = RED;
		node06->color = BLACK;
		node07->color = BLACK;
		node08->color = BLACK;
		node09->color = BLACK;
		node10->color = BLACK;
		node11->color = BLACK;
		CHECK(OK == rbt_check_status(tree));
		CHECK(node06 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node01 == tree->root);
		CHECK(node02 == node01->left);
		CHECK(node04 == node01->right);
		CHECK(node03 == node04->left);
		CHECK(node05 == node04->right);
		CHECK(node06 == node02->left);
		CHECK(node07 == node02->right);
		CHECK(node08 == node03->left);
		CHECK(node09 == node03->right);
		CHECK(node10 == node05->left);
		CHECK(node11 == node05->right);
		//delete the node from the tree
		mem_retain(node06);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node06));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node06->parent);
		CHECK(NULL == node06->left);
		CHECK(NULL == node06->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node06);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_rebalance_sib_with_two_red_children_right){
		int target = 88;
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node01 = rbt_insert(tree, 42);
		rbt_node_t* node02 = rbt_insert(tree, 55);
		rbt_node_t* node03 = rbt_insert(tree, 33);
		rbt_node_t* node04 = rbt_insert(tree, 22);
		rbt_node_t* node05 = rbt_insert(tree, 15);
		rbt_node_t* node06 = rbt_insert(tree, target);
		rbt_node_t* node07 = rbt_insert(tree, 50);
		rbt_node_t* node08 = rbt_insert(tree, 37);
		rbt_node_t* node09 = rbt_insert(tree, 28);
		rbt_node_t* node10 = rbt_insert(tree, 17);
		rbt_node_t* node11 = rbt_insert(tree, 11);
		//force colors to match scenario being tested
		(void)node01;
		node02->color = BLACK;
		node03->color = RED;
		node04->color = BLACK;
		node05->color = RED;
		node06->color = BLACK;
		node07->color = BLACK;
		node08->color = BLACK;
		node09->color = BLACK;
		node10->color = BLACK;
		node11->color = BLACK;
		CHECK(OK == rbt_check_status(tree));
		CHECK(node06 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node01 == tree->root);
		CHECK(node02 == node01->right);
		CHECK(node04 == node01->left);
		CHECK(node03 == node04->right);
		CHECK(node05 == node04->left);
		CHECK(node06 == node02->right);
		CHECK(node07 == node02->left);
		CHECK(node08 == node03->right);
		CHECK(node09 == node03->left);
		CHECK(node10 == node05->right);
		CHECK(node11 == node05->left);
		//delete the node from the tree
		mem_retain(node06);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node06));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node06->parent);
		CHECK(NULL == node06->left);
		CHECK(NULL == node06->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node06);
		mem_release(tree);
	}
	//4.2: sibbling is black, outside red child
	TEST(Verify_rbt_delete_black_node_from_black_parent_sib_has_outside_red_child_right){
		int target = 99;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 88); //root
		rbt_node_t* node2 = rbt_insert(tree, target); //target
		rbt_node_t* node3 = rbt_insert(tree, 42); //sibbling
		rbt_node_t* node4 = rbt_insert(tree, 22); //sib child
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = BLACK;
		node4->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node2 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->right);
		CHECK(node3 == node1->left);
		CHECK(node4 == node3->left);
		//delete the node from the tree
		mem_retain(node2);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node2));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node2->parent);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node2);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_black_node_from_black_parent_sib_has_outside_red_child_left){
		int target = 8;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42); //root
		rbt_node_t* node2 = rbt_insert(tree, target); //target
		rbt_node_t* node3 = rbt_insert(tree, 88); //sibbling
		rbt_node_t* node4 = rbt_insert(tree, 123); //sib child
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = BLACK;
		node4->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node2 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->left);
		CHECK(node3 == node1->right);
		CHECK(node4 == node3->right);
		//delete the node from the tree
		mem_retain(node2);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node2));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node2->parent);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node2);
		mem_release(tree);
	}
	//4.3: sibbling is black, inside red child
	TEST(Verify_rbt_delete_black_node_from_black_parent_sib_has_inside_red_child_right){
		int target = 99;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 88); //root
		rbt_node_t* node2 = rbt_insert(tree, target); //target
		rbt_node_t* node3 = rbt_insert(tree, 42); //sibbling
		rbt_node_t* node4 = rbt_insert(tree, 55); //sib child
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = BLACK;
		node4->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node2 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->right);
		CHECK(node3 == node1->left);
		CHECK(node4 == node3->right);
		//delete the node from the tree
		mem_retain(node2);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node2));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node2->parent);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node2);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_black_node_from_black_parent_sib_has_inside_red_child_left){
		int target = 8;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42); //root
		rbt_node_t* node2 = rbt_insert(tree, target); //target
		rbt_node_t* node3 = rbt_insert(tree, 88); //sibbling
		rbt_node_t* node4 = rbt_insert(tree, 70); //sib child
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = BLACK;
		node4->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node2 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->left);
		CHECK(node3 == node1->right);
		CHECK(node4 == node3->left);
		//delete the node from the tree
		mem_retain(node2);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node2));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node2->parent);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node2);
		mem_release(tree);
	}
	//4.4: sibbling is black, two red children
	TEST(Verify_rbt_delete_black_node_from_black_parent_sib_has_two_children_right){
		int target = 99;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 88); //root
		rbt_node_t* node2 = rbt_insert(tree, target); //target
		rbt_node_t* node3 = rbt_insert(tree, 42); //sibbling
		rbt_node_t* node4 = rbt_insert(tree, 22); //sib child 1
		rbt_node_t* node5 = rbt_insert(tree, 55); //sib child 2
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = BLACK;
		node4->color = RED;
		node5->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node2 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->right);
		CHECK(node3 == node1->left);
		CHECK(node4 == node3->left);
		CHECK(node5 == node3->right);
		//delete the node from the tree
		mem_retain(node2);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node2));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node2->parent);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node2);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_black_node_from_black_parent_sib_has_two_children_left){
		int target = 8;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42); //root
		rbt_node_t* node2 = rbt_insert(tree, target); //target
		rbt_node_t* node3 = rbt_insert(tree, 88); //sibbling
		rbt_node_t* node4 = rbt_insert(tree, 70); //sib child 1
		rbt_node_t* node5 = rbt_insert(tree, 123); //sib child 2
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = BLACK;
		node4->color = RED;
		node5->color = RED;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node2 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->left);
		CHECK(node3 == node1->right);
		CHECK(node4 == node3->left);
		CHECK(node5 == node3->right);
		//delete the node from the tree
		mem_retain(node2);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node2));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node2->parent);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node2);
		mem_release(tree);
	}
	//4.5: sibbling is red, two black children
	TEST(Verify_rbt_delete_black_node_from_black_parent_red_sib_right){
		int target = 99;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 88); //root
		rbt_node_t* node2 = rbt_insert(tree, target); //target
		rbt_node_t* node3 = rbt_insert(tree, 42); //sibbling
		rbt_node_t* node4 = rbt_insert(tree, 22); //sib child 1
		rbt_node_t* node5 = rbt_insert(tree, 55); //sib child 2
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node2 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->right);
		CHECK(node3 == node1->left);
		CHECK(node4 == node3->left);
		CHECK(node5 == node3->right);
		//delete the node from the tree
		mem_retain(node2);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node2));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node2->parent);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node2);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_black_node_from_black_parent_red_sib_left){
		int target = 8;
		//create tree w/ several nodes
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42); //root
		rbt_node_t* node2 = rbt_insert(tree, target); //target
		rbt_node_t* node3 = rbt_insert(tree, 88); //sibbling
		rbt_node_t* node4 = rbt_insert(tree, 70); //sib child 1
		rbt_node_t* node5 = rbt_insert(tree, 123); //sib child 2
		//force colors to match scenario being tested
		(void)node1;
		node2->color = BLACK;
		node3->color = RED;
		node4->color = BLACK;
		node5->color = BLACK;
		//confirm tree is valid & node can be found
		CHECK(OK == rbt_check_status(tree));
		CHECK(node2 == rbt_lookup(tree, target));
		//confirm tree is shaped as expected
		CHECK(node1 == tree->root);
		CHECK(node2 == node1->left);
		CHECK(node3 == node1->right);
		CHECK(node4 == node3->left);
		CHECK(node5 == node3->right);
		//delete the node from the tree
		mem_retain(node2);
		rbt_delete(tree, target);
		//confirm refcounting decremented, node no longer in tree, node pointers nulld and tree still valid
		CHECK(1 == mem_num_references(node2));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == node2->parent);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node2);
		mem_release(tree);
	}
	//second class: deleting nodes that have two children
	TEST(Verify_rbt_delete_node_with_two_children_successor_is_left){
		int target = 22;
		rbt_t* tree = rbt_new(test_compare);
		rbt_insert(tree, 42);
		rbt_insert(tree, 88);
		rbt_node_t* doomed = rbt_insert(tree, target);
		rbt_insert(tree, 33);
		rbt_insert(tree, 15);
		CHECK(NULL != doomed->left);
		CHECK(NULL != doomed->right);
		CHECK(NULL == doomed->left->right);
		CHECK(OK == rbt_check_status(tree));
		CHECK(doomed == rbt_lookup(tree, target));
		mem_retain(doomed);
		rbt_delete(tree, target);
		CHECK(1 == mem_num_references(doomed));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == doomed->parent);
		CHECK(NULL == doomed->left);
		CHECK(NULL == doomed->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(doomed);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_node_with_two_children){
		int target = 42;
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* doomed = rbt_insert(tree, target);
		rbt_insert(tree, 88);
		rbt_insert(tree, 22);
		rbt_insert(tree, 96);
		rbt_insert(tree, 11);
		rbt_insert(tree, 35);
		rbt_insert(tree, 5);
		rbt_insert(tree, 18);
		rbt_insert(tree, 12);
		rbt_insert(tree, 25);
		rbt_insert(tree, 55);
		rbt_insert(tree, 99);
		CHECK(OK == rbt_check_status(tree));
		CHECK(doomed != tree->root);
		CHECK(NULL != doomed->left);
		CHECK(NULL != doomed->right);
		CHECK(doomed == rbt_lookup(tree, target));
		mem_retain(doomed);
		rbt_delete(tree, target);
		CHECK(1 == mem_num_references(doomed));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == doomed->parent);
		CHECK(NULL == doomed->left);
		CHECK(NULL == doomed->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(doomed);
		mem_release(tree);
	}
	//third class: special cases: deleting root
	TEST(Verify_rbt_delete_root_node_with_single_red_left_child){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 88);
		rbt_node_t* node2 = rbt_insert(tree, 42);
		mem_retain(node1);
		rbt_delete(tree, 88);
		CHECK(1 == mem_num_references(node1));
		CHECK(node2 == tree->root);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(NULL == node2->parent);
		//check node1 pointers are nulld
		CHECK(NULL == node1->parent);
		CHECK(NULL == node1->left);
		CHECK(NULL == node1->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node1);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_root_node_with_single_red_right_child){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 42);
		rbt_node_t* node2 = rbt_insert(tree, 88);
		mem_retain(node1);
		rbt_delete(tree, 42);
		CHECK(1 == mem_num_references(node1));
		CHECK(node2 == tree->root);
		CHECK(NULL == node2->left);
		CHECK(NULL == node2->right);
		CHECK(NULL == node2->parent);
		//check node1 pointers are nulld
		CHECK(NULL == node1->parent);
		CHECK(NULL == node1->left);
		CHECK(NULL == node1->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node1);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_root_node_with_no_children){
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* node1 = rbt_insert(tree, 88);
		mem_retain(node1);
		rbt_delete(tree, 88);
		CHECK(1 == mem_num_references(node1));
		CHECK(NULL == tree->root);
		CHECK(NULL == node1->left);
		CHECK(NULL == node1->right);
		CHECK(NULL == node1->parent);
		CHECK(OK == rbt_check_status(tree));
		mem_release(node1);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_root_node_with_two_children){
		int target = 22;
		rbt_t* tree = rbt_new(test_compare);
		rbt_insert(tree, 42);
		rbt_insert(tree, 88);
		rbt_node_t* doomed = rbt_insert(tree, target);
		rbt_insert(tree, 96);
		rbt_insert(tree, 11);
		rbt_insert(tree, 35);
		rbt_insert(tree, 5);
		rbt_insert(tree, 18);
		rbt_insert(tree, 12);
		rbt_insert(tree, 25);
		rbt_insert(tree, 55);
		rbt_insert(tree, 99);
		CHECK(OK == rbt_check_status(tree));
		CHECK(doomed == tree->root);
		CHECK(NULL != doomed->left);
		CHECK(NULL != doomed->right);
		CHECK(doomed == rbt_lookup(tree, target));
		mem_retain(doomed);
		rbt_delete(tree, target);
		CHECK(1 == mem_num_references(doomed));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == doomed->parent);
		CHECK(NULL == doomed->left);
		CHECK(NULL == doomed->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(doomed);
		mem_release(tree);
	}
	TEST(Verify_rbt_delete_node_with_four_nodes){
		int target = 42;
		rbt_t* tree = rbt_new(test_compare);
		rbt_node_t* doomed = rbt_insert(tree, target);
		rbt_insert(tree, 88);
		rbt_insert(tree, 22);
		rbt_insert(tree, 33);
		CHECK(OK == rbt_check_status(tree));
		CHECK(doomed == tree->root);
		CHECK(NULL != doomed->left);
		CHECK(NULL != doomed->right);
		CHECK(doomed == rbt_lookup(tree, target));
		mem_retain(doomed);
		rbt_delete(tree, target);
		CHECK(1 == mem_num_references(doomed));
		CHECK(NULL == rbt_lookup(tree, target));
		CHECK(NULL == doomed->parent);
		CHECK(NULL == doomed->left);
		CHECK(NULL == doomed->right);
		CHECK(OK == rbt_check_status(tree));
		mem_release(doomed);
		mem_release(tree);
	}
	*/
}

