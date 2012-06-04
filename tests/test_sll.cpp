// Unit Test Framework Includes
#include "UnitTest++.h"
#include <cstdlib>

// File To Test
#include "sll.h"

using namespace UnitTest;

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
namespace {
    //-------------------------------------------------------------------------
    // Test sll_new function
    //-------------------------------------------------------------------------
    TEST(Verify_sll_new_returns_newly_allocated_empty_list)
    {
        sll_t* list = sll_new();
        CHECK( NULL != list );
        CHECK( NULL == list->head );
        CHECK( NULL == list->tail );
        free( list );
    }

    //-------------------------------------------------------------------------
    // Test sll_new_node function
    //-------------------------------------------------------------------------
    TEST(Verify_sll_new_node_returns_newly_allocated_node_with_given_contents)
    {
        int stuff = 0;
        sll_node_t* node = sll_new_node( &stuff );
        CHECK( NULL != node );
        CHECK( &stuff == node->contents );
        CHECK( NULL == node->next );
        free( node );
    }

    //-------------------------------------------------------------------------
    // Test sll_free function
    //-------------------------------------------------------------------------
    TEST(Verify_sll_free_does_nothing_on_null_pointer)
    {
        sll_free( NULL, 0 );
    }

    TEST(Verify_sll_free_frees_the_given_empty_list)
    {
        sll_t* list = sll_new();
        sll_free( list, 0 );
    }

    TEST(Verify_sll_free_frees_the_given_list_including_nodes)
    {
        sll_t* list = sll_new();
        list->head = sll_new_node(NULL);
        list->tail = list->head;
        sll_free( list, 0 );
    }

    TEST(Verify_sll_free_frees_the_given_list_including_nodes_and_node_contents)
    {
        sll_t* list = sll_new();
        int* foo = (int*)malloc( sizeof(int) );
        list->head = sll_new_node( foo );
        list->tail = list->head;
        sll_free( list, 1 );
    }

    //-------------------------------------------------------------------------
    // Test sll_free_node function
    //-------------------------------------------------------------------------
    TEST(Verify_sll_free_node_does_nothing_on_null_pointer)
    {
        sll_free_node( NULL, 0 );
    }

    TEST(Verify_sll_free_node_frees_the_given_node)
    {
        sll_node_t* node = sll_new_node( NULL );
        sll_free_node( node, 0 );
    }

    TEST(Verify_sll_free_node_frees_the_given_node_and_contents)
    {
        int* foo = (int*)malloc( sizeof(int) );
        sll_node_t* node = sll_new_node( foo );
        sll_free_node( node, 1 );
    }

    //-------------------------------------------------------------------------
    // Test sll_length function
    //-------------------------------------------------------------------------
    TEST(Verify_sll_length_returns_0_when_passed_null_pointer)
    {
        CHECK( 0 == sll_length(NULL) );
    }

    TEST(Verify_sll_length_returns_0_when_list_is_empty)
    {
        sll_t* list = sll_new();
        CHECK( 0 == sll_length( list ) );
        free( list );
    }

    TEST(Verify_sll_length_returns_1_when_list_is_length_1)
    {
        sll_node_t node1 = { NULL, NULL };
        sll_t list = { &node1, &node1 };

        CHECK( 1 == sll_length( &list ) );
    }

    TEST(Verify_sll_length_returns_2_when_list_is_length_2)
    {
        sll_node_t node2 = { NULL, NULL };
        sll_node_t node1 = { NULL, &node2 };
        sll_t list = { &node1, &node2 };

        CHECK( 2 == sll_length( &list ) );
    }

    //-------------------------------------------------------------------------
    // Test sll_index function
    //-------------------------------------------------------------------------
    TEST(Verify_sll_index_returns_NULL_on_null_pointer)
    {
        CHECK( NULL == sll_index( NULL, 0 ) );
    }

    TEST(Verify_sll_index_returns_NULL_when_list_is_empty)
    {
        sll_t list = { NULL, NULL };
        CHECK( NULL == sll_index( &list, 0 ) );
    }

    TEST(Verify_sll_index_returns_NULL_when_index_out_of_range)
    {
        sll_node_t node3 = { NULL, NULL };
        sll_node_t node2 = { NULL, &node3 };
        sll_node_t node1 = { NULL, &node2 };
        sll_t list = { &node1, &node3 };
        CHECK( NULL == sll_index( &list, 3 ) );
    }

    TEST(Verify_sll_index_returns_node_at_index_0_of_3_element_list)
    {
        sll_node_t node3 = { NULL, NULL };
        sll_node_t node2 = { NULL, &node3 };
        sll_node_t node1 = { NULL, &node2 };
        sll_t list = { &node1, &node3 };
        CHECK( &node1 == sll_index( &list, 0 ) );
    }

    TEST(Verify_sll_index_returns_node_at_index_1_of_3_element_list)
    {
        sll_node_t node3 = { NULL, NULL };
        sll_node_t node2 = { NULL, &node3 };
        sll_node_t node1 = { NULL, &node2 };
        sll_t list = { &node1, &node3 };
        CHECK( &node2 == sll_index( &list, 1 ) );
    }

    TEST(Verify_sll_index_returns_node_at_index_2_of_3_element_list)
    {
        sll_node_t node3 = { NULL, NULL };
        sll_node_t node2 = { NULL, &node3 };
        sll_node_t node1 = { NULL, &node2 };
        sll_t list = { &node1, &node3 };
        CHECK( &node3 == sll_index( &list, 2 ) );
    }

    //-------------------------------------------------------------------------
    // Test sll_push_front function
    //-------------------------------------------------------------------------
    TEST(Verify_sll_push_front_returns_null_if_list_is_null)
    {
        CHECK( NULL == sll_push_front( NULL, NULL ) );
    }

    TEST(Verify_sll_push_front_pushes_to_empty_list)
    {
        sll_t list = { NULL, NULL };
        sll_node_t* node = sll_push_front( &list, (void*)0x1234 );
        CHECK( NULL != node );
        CHECK( (void*)0x1234 == node->contents );
        CHECK( NULL == node->next );
        CHECK( node == list.head );
        CHECK( node == list.tail );
    }

    TEST(Verify_sll_push_front_pushes_to_front_of_list_of_length_1)
    {
        sll_node_t node1 = { NULL, NULL };
        sll_t list = { &node1, &node1 };
        sll_node_t* node = sll_push_front( &list, (void*)0x1234 );
        CHECK( NULL != node );
        CHECK( (void*)0x1234 == node->contents );
        CHECK( NULL != node->next );
        CHECK( node == list.head );
        CHECK( node == list.tail );
    }

    //-------------------------------------------------------------------------
    // Test sll_push_back function
    //-------------------------------------------------------------------------
    TEST(Verify_sll_push_back_returns_null_if_list_is_null)
    {
        CHECK( NULL == sll_push_back( NULL, NULL ) );
    }

    TEST(Verify_sll_push_back_pushes_to_empty_list)
    {
        sll_t list = { NULL, NULL };
        sll_node_t* node = sll_push_back( &list, (void*)0x1234 );
        CHECK( NULL != node );
        CHECK( (void*)0x1234 == node->contents );
        CHECK( NULL == node->next );
        CHECK( node == list.head );
        CHECK( node == list.tail );
    }

    TEST(Verify_sll_push_back_pushes_to_back_of_list_of_length_1)
    {
        sll_node_t node1 = { NULL, NULL };
        sll_t list = { &node1, &node1 };
        sll_node_t* node = sll_push_front( &list, (void*)0x1234 );
        CHECK( NULL != node );
        CHECK( (void*)0x1234 == node->contents );
        CHECK( NULL != node->next );
        CHECK( node == list.head );
        CHECK( node == list.tail );
    }

    //-------------------------------------------------------------------------
    // Test sll_pop_front function
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // Test sll_pop_back function
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // Test sll_insert function
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // Test sll_delete function
    //-------------------------------------------------------------------------
}
