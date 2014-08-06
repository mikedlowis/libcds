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
		CHECK(rb_node_is_valid(node, -1, -1));
		mem_release(node);
    }

    //-------------------------------------------------------------------------
    // Test the rb_tree_new function
    //-------------------------------------------------------------------------
	TEST(Verify_rb_tree_new_returns_an_empty_red_black_tree){
		rb_tree_t* tree = rb_tree_new();
		CHECK(NULL != tree);
		CHECK(NULL == tree->root);
		CHECK(rb_tree_is_valid(tree));
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
		CHECK(rb_tree_is_valid(tree));
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
		CHECK(rb_tree_is_valid(tree));
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
		CHECK(rb_tree_is_valid(tree));
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
		CHECK(rb_tree_is_valid(tree));
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
		CHECK(rb_tree_is_valid(tree));
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
		CHECK(rb_tree_is_valid(tree));
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
		CHECK(rb_tree_is_valid(tree));
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
		CHECK(rb_tree_is_valid(tree));
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
		CHECK(rb_tree_is_valid(tree));
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
		CHECK(rb_tree_is_valid(tree));
		mem_release(node4);
		mem_release(tree);
    }
    TEST(Verify_rb_delete_black_node_with_single_red_child){
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
		CHECK(rb_tree_is_valid(tree));
		mem_release(node2);
		mem_release(tree);
    }

	//second class: deleting nodes that have two children
	//third class: special cases
	TEST(Verify_rb_delete_root){}
}

