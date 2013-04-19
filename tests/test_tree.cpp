// Unit Test Framework Includes
#include "UnitTest++.h"
#include <cstdlib>
#include <cstdio>

// File To Test
#include "tree.h"

using namespace UnitTest;

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
namespace {
    //-------------------------------------------------------------------------
    // Test tree_new function
    //-------------------------------------------------------------------------
    TEST(Verify_tree_new_allocates_a_new_tree_with_default_compare_fn)
    {
        tree_t* tree = tree_new(NULL);
        CHECK(tree != NULL);
        CHECK(tree->cmp_fn != NULL);
        CHECK(tree->size == 0);
        CHECK(tree->root == NULL);
        tree_free( tree, false );
    }

    TEST(Verify_tree_new_allocates_a_new_tree_with_provided_compare_fn)
    {
        tree_t* tree = tree_new( (tree_cmp_fn_t)0x1234 );
        CHECK(tree != NULL);
        CHECK(tree->cmp_fn == (tree_cmp_fn_t)0x1234);
        CHECK(tree->size == 0);
        CHECK(tree->root == NULL);
        tree_free( tree, false );
    }

    //-------------------------------------------------------------------------
    // Test tree_new_node function
    //-------------------------------------------------------------------------
    TEST(Verify_tree_new_node_allocates_a_new_tree_node_with_the_given_value)
    {
        tree_node_t* node = tree_new_node((void*)0x1234);
        CHECK( node->value == (void*)0x1234);
        CHECK( node->left == NULL);
        CHECK( node->right == NULL);
        tree_free_node( node, false );
    }

    //-------------------------------------------------------------------------
    // Test tree_cmp_ptrs function
    //-------------------------------------------------------------------------
    TEST(Verify_tree_cmp_ptrs_returns_0_when_pointers_equal)
    {
        CHECK(0 == tree_cmp_ptrs((void*)0x1234,(void*)0x1234));
    }

    TEST(Verify_tree_cmp_ptrs_returns_negative_when_tree_pointer_is_less_than_free_pointer)
    {
        CHECK(-1 == tree_cmp_ptrs((void*)0x1234,(void*)0x1235));
    }

    TEST(Verify_tree_cmp_ptrs_returns_positive_when_tree_pointer_is_greater_than_free_pointer)
    {
        CHECK(1 == tree_cmp_ptrs((void*)0x1234,(void*)0x1233));
    }

    //-------------------------------------------------------------------------
    // Test tree_empty function
    //-------------------------------------------------------------------------
    TEST(Verify_tree_empty_returns_true_if_tree_is_empty)
    {
        tree_t tree = { NULL, 0, NULL };
        CHECK( true == tree_empty( &tree ) );
    }

    TEST(Verify_tree_empty_returns_false_if_tree_is_not_empty)
    {
        tree_t tree = { NULL, 1, NULL };
        CHECK( false == tree_empty( &tree ) );
    }

    //-------------------------------------------------------------------------
    // Test tree_size function
    //-------------------------------------------------------------------------
    TEST(Verify_tree_size_returns_the_number_of_elements_in_the_tree)
    {
        tree_t tree = { NULL, 42, NULL };
        CHECK( 42 == tree_size( &tree ) );
    }

    //-------------------------------------------------------------------------
    // Test tree_max_size function
    //-------------------------------------------------------------------------
    TEST(Verify_max_size_returns_the_maximum_number_of_elements_a_tree_can_hold)
    {
        CHECK( (size_t)-1 == tree_max_size() );
    }

    //-------------------------------------------------------------------------
    // Test tree_insert function
    //-------------------------------------------------------------------------
    TEST(Verify_tree_insert_inserts_the_value_in_the_empty_tree)
    {
        tree_t* tree = tree_new(NULL);
        tree_insert(tree,(void*)0x1234);
        CHECK( tree->root != NULL );
        CHECK( tree->root->value == (void*)0x1234 );
        CHECK( tree->root->left == NULL );
        CHECK( tree->root->right == NULL );
        CHECK( tree->size == 1 );
        tree_free(tree,false);
    }

    TEST(Verify_tree_insert_inserts_the_value_as_a_left_child)
    {
        tree_t* tree = tree_new(NULL);
        tree_insert(tree,(void*)0x1234);
        tree_insert(tree,(void*)0x1233);

        CHECK( tree->root->left != NULL );
        tree_node_t* node = (tree_node_t*)tree->root->left;
        CHECK( node->value == (void*)0x1233 );
        CHECK( node->left == NULL );
        CHECK( node->right == NULL );
        CHECK( tree->size == 2 );

        tree_free(tree,false);
    }

    TEST(Verify_tree_insert_inserts_the_value_as_a_right_child)
    {
        tree_t* tree = tree_new(NULL);
        tree_insert(tree,(void*)0x1234);
        tree_insert(tree,(void*)0x1235);

        CHECK( tree->root->right != NULL );
        tree_node_t* node = (tree_node_t*)tree->root->right;
        CHECK( node->value == (void*)0x1235 );
        CHECK( node->left == NULL );
        CHECK( node->right == NULL );
        CHECK( tree->size == 2 );

        tree_free(tree,false);
    }

    TEST(Verify_tree_insert_does_nothing_when_identical_node_already_exists)
    {
        tree_t* tree = tree_new(NULL);
        tree_insert(tree,(void*)0x1234);
        tree_insert(tree,(void*)0x1234);
        CHECK( tree->root != NULL );
        CHECK( tree->root->value == (void*)0x1234 );
        CHECK( tree->root->left == NULL );
        CHECK( tree->root->right == NULL );
        CHECK( tree->size == 1 );
        tree_free(tree,false);
    }

    //-------------------------------------------------------------------------
    // Test tree_at function
    //-------------------------------------------------------------------------
    TEST(Verify_tree_at_returns_the_item_if_found)
    {
        tree_t* tree = tree_new(NULL);
        tree_insert(tree,(void*)0x1234);
        tree_insert(tree,(void*)0x1233);
        tree_insert(tree,(void*)0x1235);
        CHECK( (void*)0x1234 == tree_at(tree,(void*)0x1234) );
        tree_free(tree,false);
    }

    TEST(Verify_tree_at_returns_null_if_tem_not_found)
    {
        tree_t* tree = tree_new(NULL);
        tree_insert(tree,(void*)0x1234);
        tree_insert(tree,(void*)0x1233);
        tree_insert(tree,(void*)0x1235);
        CHECK( (void*)NULL == tree_at(tree,(void*)0x1236) );
        tree_free(tree,false);
    }

    //-------------------------------------------------------------------------
    // Test tree_erase function
    //-------------------------------------------------------------------------
    TEST(Verify_tree_erase_erases_the_node_with_the_matching_value)
    {
    }

    //-------------------------------------------------------------------------
    // Test tree_clear function
    //-------------------------------------------------------------------------
    TEST(Verify_tree_clear_erases_all_nodes_in_the_tree)
    {
        tree_t* tree = tree_new(NULL);
        tree_insert(tree,(void*)0x1234);
        tree_insert(tree,(void*)0x1233);
        tree_insert(tree,(void*)0x1235);

        tree_clear(tree,false);
        CHECK(tree != NULL);
        CHECK(tree->cmp_fn != NULL);
        CHECK(tree->size == 0);
        CHECK(tree->root == NULL);

        tree_free(tree,false);
    }
}
