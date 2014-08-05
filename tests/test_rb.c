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
    // Test the rb_new functions
    //-------------------------------------------------------------------------
    TEST(Verify_rb_node_new_returns_a_new_node){
		rb_node_t* node = rb_node_new(42);
		CHECK(NULL != node);
		CHECK(NULL == node->left);
		CHECK(NULL == node->right);
		CHECK(42 == node->contents);
		mem_release(node);
    }

	TEST(Verify_rb_tree_new_returns_an_empty_red_black_tree){
		rb_tree_t* rb = rb_tree_new();
		CHECK(rb != NULL);
		CHECK(rb->root == NULL);
		mem_release(rb);
	}

}

