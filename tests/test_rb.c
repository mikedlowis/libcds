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
    /*
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
		CHECK(
		CHECK(rb_tree_is_valid(tree));
		mem_release(tree);
    }
    */
}

