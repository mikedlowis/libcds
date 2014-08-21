// Unit Test Framework Includes
#include "test.h"

// File To Test
#include "list.h"
#include "mem.h"

static void test_setup(void) { }

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
TEST_SUITE(List) {
    //-------------------------------------------------------------------------
    // Test list_new function
    //-------------------------------------------------------------------------
    TEST(Verify_list_new_returns_newly_allocated_empty_list)
    {
        list_t* list = list_new();
        CHECK( NULL != list );
        CHECK( NULL == list->head );
        CHECK( NULL == list->tail );
        mem_release( list );
    }

    //-------------------------------------------------------------------------
    // Test list_new_node function
    //-------------------------------------------------------------------------
    TEST(Verify_list_new_node_returns_newly_allocated_node_with_given_contents)
    {
        list_node_t* node = list_new_node( mem_box(88) );
        CHECK( NULL != node );
        CHECK( 88 == mem_unbox(node->contents) );
        CHECK( NULL == node->next );
        CHECK( NULL == node->prev );
        mem_release( node );
    }

    //-------------------------------------------------------------------------
    // Test list_front function
    //-------------------------------------------------------------------------
    TEST(Verify_list_front_returns_NULL_if_list_is_empty)
    {
        list_t* list = list_new();
        CHECK( NULL == list_front( list ) );
        mem_release( list );
    }

    TEST(Verify_list_front_returns_the_head_of_the_list)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back(list, mem_box(0x4242));
        list_node_t* node2 = list_push_back(list, mem_box(0x8888));
        CHECK( node1 == list_front( list ) );
        (void)node2;
        mem_release( list );
    }

    //-------------------------------------------------------------------------
    // Test list_back function
    //-------------------------------------------------------------------------
    TEST(Verify_list_back_returns_NULL_if_list_is_empty)
    {
        list_t* list = list_new();
        CHECK( NULL == list_back( list ) );
        mem_release( list );
    }

    TEST(Verify_list_back_returns_the_tail_of_the_list)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back(list, mem_box(0x4288));
        list_node_t* node2 = list_push_back(list, mem_box(0x8842));
        (void)node1;
        CHECK( node2 == list_back( list ) );
        mem_release( list );
    }

    //-------------------------------------------------------------------------
    // Test list_size function
    //-------------------------------------------------------------------------
    TEST(Verify_list_size_returns_0_when_list_is_empty)
    {
        list_t* list = list_new();
        CHECK( 0 == list_size( list ) );
        mem_release( list );
    }

    TEST(Verify_list_size_returns_1_when_list_is_length_1)
    {
        list_t* list = list_new();
        list_push_back(list, mem_box(0x1234));
        CHECK( 1 == list_size( list ) );
        mem_release( list );
    }

    TEST(Verify_list_size_returns_2_when_list_is_length_2)
    {
        list_t* list = list_new();
        list_push_back(list, mem_box(0x8888));
        list_push_back(list, mem_box(0x9999));
        CHECK( 2 == list_size( list ) );
        mem_release( list );
    }

    //-------------------------------------------------------------------------
    // Test list_empty function
    //-------------------------------------------------------------------------
    TEST(Verify_list_empty_returns_true_when_head_and_tail_are_null)
    {
        list_t* list = list_new();
        CHECK( true == list_empty( list ) );
        mem_release( list );
    }

    TEST(Verify_list_empty_returns_false_when_list_not_empty)
    {
        list_t* list = list_new();
        list_push_back(list, mem_box(0x1234));
        CHECK( false == list_empty( list ) );
        mem_release( list );
    }

    //-------------------------------------------------------------------------
    // Test list_prev function
    //-------------------------------------------------------------------------
    TEST(Verify_list_prev_returns_NULL_when_list_is_empty)
    {
        list_t* list = list_new();
        list_node_t* bogus = list_new_node(NULL);
        CHECK( NULL == list_prev(list, NULL) );
        CHECK( NULL == list_prev(list, bogus) );
        mem_release( bogus );
        mem_release( list );
    }

    TEST(Verify_list_prev_returns_NULL_when_given_NULL)
    {
        list_t* list = list_new();
        list_push_back(list, mem_box(0x1234));
        list_push_back(list, mem_box(0x8888));
        list_push_back(list, mem_box(0x9876));
        CHECK( NULL == list_prev(list, NULL) );
        mem_release( list );
    }

    TEST(Verify_list_prev_returns_NULL_when_given_node_not_present)
    {
        list_t* list = list_new();
        list_node_t* bogus = list_new_node(NULL);
        list_push_back(list, mem_box(0x4321));
        list_push_back(list, mem_box(0x2a2a));
        list_push_back(list, mem_box(0x6666));
        CHECK( NULL == list_prev(list, bogus) );
        mem_release( bogus );
        mem_release( list );
    }

    TEST(Verify_list_prev_returns_NULL_when_given_node_at_head)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back(list, mem_box(0x8888));
        list_push_back(list, mem_box(0x9876));
        list_push_back(list, mem_box(0x1234));
        CHECK( NULL == list_prev(list, node1) );
        mem_release( list );
    }

    TEST(Verify_list_prev_returns_previous_node)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back(list, mem_box(0x9876));
        list_node_t* node2 = list_push_back(list, mem_box(0x8888));
        list_node_t* node3 = list_push_back(list, mem_box(0x1234));
        list_node_t* node4 = list_push_back(list, mem_box(0x4321));
        CHECK( node1 == list_prev(list, node2) );
        CHECK( node2 == list_prev(list, node3) );
        CHECK( node3 == list_prev(list, node4) );
        mem_release( list );
    }

    //-------------------------------------------------------------------------
    // Test list_at function
    //-------------------------------------------------------------------------
    TEST(Verify_list_at_returns_NULL_when_list_is_empty)
    {
        list_t* list = list_new();
        CHECK( NULL == list_at( list, 0 ) );
        mem_release( list );
    }

    TEST(Verify_list_at_returns_NULL_when_index_out_of_range)
    {
        list_t* list = list_new();
        list_push_back(list, mem_box(0x2a2a));
        list_push_back(list, mem_box(0x4242));
        list_push_back(list, mem_box(0x9876));
        CHECK( NULL == list_at( list, 3 ) );
        mem_release( list );
    }

    TEST(Verify_list_at_returns_node_at_given_index)
    {
        list_t* list = list_new();
        list_node_t* node0 = list_push_back(list, mem_box(0x8888));
        list_node_t* node1 = list_push_back(list, mem_box(0x4242));
        list_node_t* node2 = list_push_back(list, mem_box(0x9876));
        CHECK( node0 == list_at( list, 0 ) );
        CHECK( node1 == list_at( list, 1 ) );
        CHECK( node2 == list_at( list, 2 ) );
        mem_release( list );
    }

    //-------------------------------------------------------------------------
    // Test list_index_of function
    //-------------------------------------------------------------------------
    TEST(Verify_list_index_of_returns_negative_one_when_list_is_empty)
    {
        list_t* list = list_new();
        list_node_t* bogus = list_new_node(NULL);
        CHECK( -1 == list_index_of(list, bogus) );
        mem_release( bogus );
        mem_release( list );
    }

    TEST(Verify_list_index_of_returns_negative_one_when_node_is_not_found)
    {
        list_t* list = list_new();
        list_push_back(list, mem_box(0x1234));
        list_push_back(list, mem_box(0x8888));
        list_push_back(list, mem_box(0x9876));
        list_node_t* bogus = list_new_node(NULL);
        CHECK( -1 == list_index_of(list, bogus) );
        mem_release( bogus );
        mem_release( list );
    }

    TEST(Verify_list_index_of_returns_list_size_when_node_is_null)
    {
        list_t* list = list_new();
        CHECK( 0 == list_index_of(list, NULL) );
        list_push_back(list, mem_box(0x1234));
        CHECK( 1 == list_index_of(list, NULL) );
        list_push_back(list, mem_box(0x9876));
        CHECK( 2 == list_index_of(list, NULL) );
        list_push_back(list, mem_box(0x8888));
        CHECK( 3 == list_index_of(list, NULL) );
        mem_release( list );
    }

    TEST(Verify_list_index_of_returns_index_of_item_in_list)
    {
        list_t* list = list_new();
        list_node_t* node0 = list_push_back(list, mem_box(0x1111));
        list_node_t* node1 = list_push_back(list, mem_box(0x2222));
        list_node_t* node2 = list_push_back(list, mem_box(0x3333));
        CHECK( 0 == list_index_of(list, node0) );
        CHECK( 1 == list_index_of(list, node1) );
        CHECK( 2 == list_index_of(list, node2) );
        mem_release( list );
    }


    //-------------------------------------------------------------------------
    // Test list_push_front function
    //-------------------------------------------------------------------------
    TEST(Verify_list_push_front_pushes_to_empty_list)
    {
        list_t* list = list_new();
        list_node_t* node = list_push_front( list, mem_box(0x1234) );
        CHECK( NULL != node );
        CHECK( 0x1234 == mem_unbox(node->contents) );
        CHECK( NULL == node->next );
        CHECK( NULL == node->prev );
        CHECK( node == list->head );
        CHECK( node == list->tail );
        mem_release(list);
    }

    TEST(Verify_list_push_front_pushes_to_front_of_list_of_length_1)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_front( list, mem_box(0x1234) );
        list_node_t* node2 = list_push_front( list, mem_box(0x1235) );
        CHECK( 0x1235 == mem_unbox(list->head->contents) );
        CHECK( node2 == list->head );
        CHECK( node1 == list->tail );
        CHECK( NULL == node2->prev );
        CHECK( node1 == node2->next );
        CHECK( node2 == node1->prev );
        CHECK( NULL == node1->next );
        mem_release(list);
    }

    //-------------------------------------------------------------------------
    // Test list_push_back function
    //-------------------------------------------------------------------------
    TEST(Verify_list_push_back_pushes_to_empty_list)
    {
        list_t* list = list_new();
        list_node_t* node = list_push_back( list, mem_box(0x1234) );
        CHECK( NULL != node );
        CHECK( 0x1234 == mem_unbox(node->contents) );
        CHECK( NULL == node->next );
        CHECK( NULL == node->prev );
        CHECK( node == list->head );
        CHECK( node == list->tail );
        mem_release(list);
    }

    TEST(Verify_list_push_back_pushes_to_back_of_list_of_length_1)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back( list, mem_box(0x1234) );
        list_node_t* node2 = list_push_back( list, mem_box(0x1235) );
        CHECK( NULL != node2 );
        CHECK( 0x1235 == mem_unbox(node2->contents) );
        CHECK( node1 == list->head );
        CHECK( node2 == list->tail );
        CHECK( NULL == node1->prev );
        CHECK( node2 == node1->next );
        CHECK( node1 == node2->prev );
        CHECK( NULL == node2->next );
        mem_release(list);
    }

    //-------------------------------------------------------------------------
    // Test list_pop_front function
    //-------------------------------------------------------------------------
    TEST(Verify_pop_front_returns_null_if_list_is_empty)
    {
        list_t* list = list_new();
        CHECK( NULL == list_pop_front( list ) );
        mem_release( list );
    }

    TEST(Verify_pop_front_removes_a_node_from_the_front_of_a_list_of_length_1)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back(list, mem_box(0x9876));
        CHECK( node1 == list_pop_front( list ) );
        CHECK( NULL == list->head );
        CHECK( NULL == list->tail );
        CHECK( NULL == node1->next );
        CHECK( NULL == node1->prev );
        mem_release( node1 );
        mem_release( list );
    }

    TEST(Verify_pop_front_removes_a_node_from_the_front_of_a_list_of_length_2)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back(list, mem_box(0x2a2a));
        list_node_t* node2 = list_push_back(list, mem_box(0x8888));
        CHECK( node1 == list_pop_front( list ) );
        CHECK( node2 == list->head );
        CHECK( node2 == list->tail );
        CHECK( NULL == node2->prev );
        CHECK( NULL == node1->next );
        CHECK( NULL == node1->prev );
        mem_release( node1 );
        mem_release( list );
    }

    TEST(Verify_pop_front_removes_a_node_from_the_front_of_a_list_of_length_3)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back(list, mem_box(0x1234));
        list_node_t* node2 = list_push_back(list, mem_box(0x4444));
        list_node_t* node3 = list_push_back(list, mem_box(0x8888));
        CHECK( node1 == list_pop_front( list ) );
        CHECK( node2 == list->head );
        CHECK( node3 == list->tail );
        CHECK( NULL == node2->prev );
        CHECK( NULL == node1->next );
        CHECK( NULL == node1->prev );
        mem_release( node1 );
        mem_release( list );
    }

    //-------------------------------------------------------------------------
    // Test list_pop_back function
    //-------------------------------------------------------------------------
    TEST(Verify_pop_back_does_nothing_if_list_is_empty)
    {
        list_t* list = list_new();
        CHECK( NULL == list_pop_back( list ) );
        mem_release( list );
    }

    TEST(Verify_pop_back_removes_a_node_from_the_back_of_a_list_of_length_1)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back(list, mem_box(0x8888));
        CHECK( node1 == list_pop_back( list ) );
        CHECK( NULL == list->head );
        CHECK( NULL == list->tail );
        CHECK( NULL == node1->next );
        CHECK( NULL == node1->prev );
        mem_release( node1 );
        mem_release( list );
    }

    TEST(Verify_pop_back_removes_a_node_from_the_back_of_a_list_of_length_2)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back(list, mem_box(0x1234));
        list_node_t* node2 = list_push_back(list, mem_box(0x8888));
        CHECK( node2 == list_pop_back( list ) );
        CHECK( node1 == list->head );
        CHECK( node1 == list->tail );
        CHECK( node2->prev == NULL);
        CHECK( node2->next == NULL);
        CHECK( node1->next == NULL);
        mem_release( node2 );
        mem_release( list );
    }

    TEST(Verify_pop_back_removes_a_node_from_the_back_of_a_list_of_length_3)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back(list, mem_box(0x2222));
        list_node_t* node2 = list_push_back(list, mem_box(0x8888));
        list_node_t* node3 = list_push_back(list, mem_box(0x9999));
        CHECK( node3 == list_pop_back( list ) );
        CHECK( node1 == list->head );
        CHECK( node2 == list->tail );
        CHECK( node2->next == NULL );
        CHECK( node3->next == NULL );
        CHECK( node3->prev == NULL );
        mem_release( node3 );
        mem_release( list );
    }

    //-------------------------------------------------------------------------
    // Test list_insert function
    //-------------------------------------------------------------------------
    TEST(Verify_insert_should_insert_into_empty_list)
    {
        list_t* list = list_new();
        list_node_t* node = list_insert( list, 0, mem_box(0x1234) );
        CHECK( node != NULL );
        CHECK( node->next == NULL );
        CHECK( node->prev == NULL );
        CHECK( mem_unbox(node->contents) == 0x1234 );
        CHECK( list->head == node );
        CHECK( list->tail == node );
        mem_release(list);
    }

    TEST(Verify_insert_should_push_to_the_front_of_the_list_if_index_is_0)
    {
        list_t* list = list_new();
        list_node_t* node2 = list_insert( list, 0, mem_box(0x1234) );
        list_node_t* node1 = list_insert( list, 0, mem_box(0x8888) );
        CHECK( node1 != NULL );
        CHECK( node1->next == node2 );
        CHECK( node1->prev == NULL );
        CHECK( node2->prev == node1 );
        CHECK( list->head == node1 );
        CHECK( list->tail == node2 );
        CHECK( mem_unbox(node1->contents) == 0x8888 );
        mem_release(list);
    }

    TEST(Verify_insert_should_insert_at_the_given_index_if_index_is_non_zero)
    {
        list_t* list = list_new();
        list_node_t* node3 = list_insert( list, 0, mem_box(0x1234) );
        list_node_t* node2 = list_insert( list, 0, mem_box(0x1235) );
        list_node_t* node1 = list_insert( list, 0, mem_box(0x1236) );
        list_node_t* newd = list_insert( list, 1, mem_box(0x1237) );
        CHECK( newd != NULL );
        CHECK( NULL == node1->prev );
        CHECK( newd == node1->next );
        CHECK( node1 == newd->prev );
        CHECK( node2 == newd->next );
        CHECK( newd == node2->prev );
        CHECK( node3 == node2->next );
        CHECK( node1 == list->head );
        CHECK( node3 == list->tail );
        CHECK( mem_unbox(newd->contents) == 0x1237 );
        mem_release(list);
    }

    TEST(Verify_insert_should_set_the_tail_of_the_list_if_index_is_the_last_item)
    {
        list_t* list = list_new();
        list_node_t* node2 = list_insert( list, 0, mem_box(0x1236) );
        list_node_t* node1 = list_insert( list, 0, mem_box(0x1235) );
        list_node_t* newd = list_insert( list, 2, mem_box(0x1234) );
        CHECK( newd != NULL );
        CHECK( node1 == list->head );
        CHECK( newd == list->tail );
        CHECK( node2->next == newd );
        CHECK( node2->prev == node1 );
        CHECK( newd->prev == node2 );
        CHECK( newd->next == NULL );
        CHECK( mem_unbox(newd->contents) == 0x1234 );
        mem_release(list);
    }

    TEST(Verify_insert_should_return_null_if_index_out_of_range)
    {
        list_t* list = list_new();
        list_insert( list, 0, mem_box(0x1236) );
        list_insert( list, 0, mem_box(0x1235) );
        list_node_t* node = list_insert( list, 3, mem_box(0x1234) );
        CHECK( node == NULL );
        mem_release(list);
    }
    TEST(Verify_insert_releases_if_index_out_of_bounds)
    {
        list_t* list = list_new();
        void* box88 = mem_box(88);
        list_push_back(list, mem_box(0x1234));
        mem_retain(box88);
        list_insert(list, 8, box88);
        CHECK(1 == mem_num_references(box88))
        mem_release(list);
        mem_release(box88);
    }

    //-------------------------------------------------------------------------
    // Test list_insert_after function
    //-------------------------------------------------------------------------
    TEST(Verify_insert_after_should_to_insert_to_head_if_node_is_null_and_list_is_empty)
    {
        list_t* list = list_new();
        list_node_t* node = list_insert_after(list, NULL, mem_box(0x1234) );
        CHECK( node == list->head );
        CHECK( node == list->tail );
        CHECK( NULL == node->next );
        CHECK( NULL == node->prev );
        mem_release(list);
    }

    TEST(Verify_insert_after_should_insert_to_head_if_node_is_null_and_list_is_populated)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_insert_after(list, NULL, mem_box(0x0666));
        list_node_t* node2 = list_insert_after(list, NULL, mem_box(0x4242));
        CHECK( node2 == list->head );
        CHECK( node1 == list->tail );
        CHECK( node1 == node2->next );
        CHECK( NULL == node2->prev );
        CHECK( NULL == node1->next );
        CHECK( node2 == node1->prev );
        list_node_t* node3 = list_insert_after(list, NULL, mem_box(0x1234));
        CHECK( node3 == list->head );
        CHECK( node1 == list->tail );
        CHECK( node2 == node3->next );
        CHECK( NULL == node3->prev );
        CHECK( node1 == node2->next );
        CHECK( node3 == node2->prev );
        CHECK( NULL == node1->next );
        CHECK( node2 == node1->prev );
        mem_release(list);
    }

    TEST(Verify_insert_after_can_build_list_linearly)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_insert_after(list, list->tail, mem_box(0x1234));
        CHECK( node1 == list->head );
        CHECK( node1 == list->tail );
        CHECK( NULL == node1->next );
        CHECK( NULL == node1->prev );
        list_node_t* node2 = list_insert_after(list, list->tail, mem_box(0x4321));
        CHECK( node1 == list->head );
        CHECK( node2 == list->tail );
        CHECK( node2 == node1->next );
        CHECK( NULL == node1->prev );
        CHECK( NULL == node2->next );
        CHECK( node1 == node2->prev );
        list_node_t* node3 = list_insert_after(list, list->tail, mem_box(0x4242));
        CHECK( node1 == list->head );
        CHECK( node3 == list->tail );
        CHECK( node2 == node1->next );
        CHECK( NULL == node1->prev );
        CHECK( node3 == node2->next );
        CHECK( node1 == node2->prev );
        CHECK( NULL == node3->next );
        CHECK( node2 == node3->prev );
        mem_release(list);
    }

    TEST(Verify_insert_after_should_insert_after_the_head_node)
    {
        list_t* list = list_new();
        list_node_t* head = list_push_back(list, mem_box(0x1234));
        list_node_t* node = list_insert_after( list, list_front(list), mem_box(0x1235) );
        CHECK( node != NULL );
        CHECK( node->next == NULL );
        CHECK( node->prev == head );
        CHECK( head->next == node );
        CHECK( list->head == head );
        CHECK( list->tail == node );
        mem_release(list);
    }

    TEST(Verify_insert_after_should_insert_after_the_tail_node)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back(list, mem_box(0x1234));
        list_node_t* node2 = list_push_back(list, mem_box(0x4321));
        list_node_t* newd = list_insert_after( list, list_back(list), mem_box(0x8888) );
        (void)node1;
        CHECK( newd != NULL );
        CHECK( newd->prev == node2 );
        CHECK( newd->next == NULL );
        CHECK( list_at(list, 2) == newd );
        CHECK( list->tail == newd );
        mem_release(list);
    }

    TEST(Verify_insert_after_should_insert_after_an_inner_node)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back(list, mem_box(0x1234));
        list_node_t* node2 = list_push_back(list, mem_box(0x1234));
        list_node_t* node3 = list_push_back(list, mem_box(0x1234));
        list_node_t* newd = list_insert_after( list, node2, mem_box(0x1234) );
        CHECK( newd != NULL );
        CHECK( node2->prev == node1 );
        CHECK( node2->next == newd );
        CHECK( newd->prev == node2 );
        CHECK( newd->next == node3 );
        CHECK( newd == list_at(list,2) );
        CHECK( node3->prev == newd );
        mem_release(list);
    }

    //-------------------------------------------------------------------------
    // Test list_delete function
    //-------------------------------------------------------------------------
    TEST(Verify_delete_deletes_the_first_element_of_a_list_of_length_1)
    {
        list_t* list = list_new();
        list_node_t* doomed = list_push_back(list, mem_box(0x1234));
        mem_retain(doomed);
        list_delete(list, 0);
        CHECK( list->head == NULL );
        CHECK( list->tail == NULL );
        CHECK( 1 == mem_num_references(doomed) );
        CHECK( NULL == doomed->next );
        CHECK( NULL == doomed->prev );
        mem_release(doomed);
        mem_release(list);
    }

    TEST(Verify_delete_deletes_the_first_element_of_a_list_of_length_2)
    {
        list_t* list = list_new();
        list_node_t* doomed = list_push_back(list, mem_box(0x1234));
        list_node_t* node1 = list_push_back(list, mem_box(0x1235));
        mem_retain(doomed);
        list_delete( list, 0);
        CHECK( list->head == node1 );
        CHECK( list->tail == node1 );
        CHECK( NULL == node1->next );
        CHECK( NULL == node1->prev );
        CHECK( mem_unbox(list->head->contents) == 0x1235 );
        CHECK( 1 == mem_num_references(doomed) );
        CHECK( NULL == doomed->next );
        CHECK( NULL == doomed->prev );
        mem_release(doomed);
        mem_release(list);
    }

    TEST(Verify_delete_deletes_element_1_of_a_list_of_length_3)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back(list, mem_box(0x1234));
        list_node_t* doomed = list_push_back(list, mem_box(0x1235));
        list_node_t* node2 = list_push_back(list, mem_box(0x1236));
        mem_retain(doomed);
        list_delete( list, 1);
        CHECK( 2 == list_size( list ) );
        CHECK( list->head == node1 );
        CHECK( list->tail == node2 );
        CHECK( node1->prev == NULL );
        CHECK( node1->next == node2 );
        CHECK( node2->prev == node1 );
        CHECK( node2->next == NULL );
        CHECK( 1 == mem_num_references(doomed) );
        CHECK( NULL == doomed->next );
        CHECK( NULL == doomed->prev );
        mem_release(doomed);
        mem_release(list);
    }

    TEST(Verify_delete_deletes_element_1_of_a_list_of_length_2)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_back(list,mem_box(0x1234));
        list_node_t* doomed = list_push_back(list,mem_box(0x1235));
        mem_retain(doomed);
        list_delete( list, 1);
        CHECK( list->head == node1 );
        CHECK( list->tail == node1 );
        CHECK( NULL == node1->next );
        CHECK( NULL == node1->prev );
        CHECK( mem_unbox(list->head->contents) == 0x1234 );
        CHECK( 1 == mem_num_references(doomed) );
        CHECK( NULL == doomed->next );
        CHECK( NULL == doomed->prev );
        mem_release(doomed);
        mem_release(list);
    }

    //-------------------------------------------------------------------------
    // Test list_delete_node function
    //-------------------------------------------------------------------------

    TEST(Verify_delete_node_deletes_the_head_node_of_a_list_of_length_1)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_insert_after(list, NULL, mem_box(0x1337));
        mem_retain(node1);
        list_delete_node(list, node1);
        CHECK( 1 == mem_num_references(node1) );
        CHECK( NULL == node1->next );
        CHECK( NULL == node1->prev );
        CHECK( NULL == list->head );
        CHECK( NULL == list->tail );
        mem_release(list);
        mem_release(node1);
    }

    TEST(Verify_delete_node_deletes_the_first_element_of_a_list_of_length_2)
    {
        list_t* list = list_new();
        list_node_t* node2 = list_insert_after(list, NULL, mem_box(0xDEAD));
        list_node_t* node1 = list_insert_after(list, NULL, mem_box(0xBEEF));
        mem_retain(node1);
        list_delete_node(list, node1);
        CHECK( 1 == mem_num_references(node1) );
        CHECK( NULL == node1->next );
        CHECK( NULL == node1->prev );
        CHECK( node2 == list->head );
        CHECK( NULL == node2->prev );
        CHECK( NULL == node2->next );
        CHECK( node2 == list->tail );
        mem_release(list);
        mem_release(node1);
    }

    TEST(Verify_delete_node_deletes_the_second_element_of_a_list_of_length_2)
    {
        list_t* list = list_new();
        list_node_t* node2 = list_insert_after(list, NULL, mem_box(0xBEAD));
        list_node_t* node1 = list_insert_after(list, NULL, mem_box(0xDAD0));
        mem_retain(node2);
        list_delete_node(list, node2);
        CHECK( 1 == mem_num_references(node2) );
        CHECK( NULL == node2->prev );
        CHECK( NULL == node2->next );
        CHECK( node1 == list->head );
        CHECK( NULL == node1->prev );
        CHECK( NULL == node1->next );
        CHECK( node1 == list->tail );
        mem_release(list);
        mem_release(node2);
    }

    TEST(Verify_delete_node_deletes_the_first_element_of_a_list_of_length_3)
    {
        list_t* list = list_new();
        list_node_t* node3 = list_insert_after(list, NULL, mem_box(0x1337));
        list_node_t* node2 = list_insert_after(list, NULL, mem_box(0x1234));
        list_node_t* node1 = list_insert_after(list, NULL, mem_box(0x4321));
        mem_retain(node1);
        list_delete_node(list, node1);
        CHECK( 1 == mem_num_references(node1) );
        CHECK( NULL == node1->prev );
        CHECK( NULL == node1->next );
        CHECK( node2 == list->head );
        CHECK( NULL == node2->prev );
        CHECK( node3 == node2->next );
        CHECK( node2 == node3->prev );
        CHECK( NULL == node3->next );
        CHECK( node3 == list->tail );
        mem_release(list);
        mem_release(node1);
    }

    TEST(Verify_delete_node_deletes_the_second_element_of_a_list_of_length_3)
    {
        list_t* list = list_new();
        list_node_t* node3 = list_insert_after(list, NULL, mem_box(0x1337));
        list_node_t* node2 = list_insert_after(list, NULL, mem_box(0x4242));
        list_node_t* node1 = list_insert_after(list, NULL, mem_box(0xBEEF));
        mem_retain(node2);
        list_delete_node(list, node2);
        CHECK( 1 == mem_num_references(node2) );
        CHECK( NULL == node2->prev );
        CHECK( NULL == node2->next );
        CHECK( node1 == list->head );
        CHECK( NULL == node1->prev );
        CHECK( node3 == node1->next );
        CHECK( node1 == node3->prev );
        CHECK( NULL == node3->next );
        CHECK( node3 == list->tail );
        mem_release(list);
        mem_release(node2);
    }

    TEST(Verify_delete_node_deletes_the_third_element_of_a_list_of_length_3)
    {
        list_t* list = list_new();
        list_node_t* node3 = list_insert_after(list, NULL, mem_box(0x4321));
        list_node_t* node2 = list_insert_after(list, NULL, mem_box(0x4242));
        list_node_t* node1 = list_insert_after(list, NULL, mem_box(0x1337));
        mem_retain(node3);
        list_delete_node(list, node3);
        CHECK( 1 == mem_num_references(node3) );
        CHECK( NULL == node3->prev );
        CHECK( NULL == node3->next );
        CHECK( node1 == list->head );
        CHECK( NULL == node1->prev );
        CHECK( node2 == node1->next );
        CHECK( node1 == node2->prev );
        CHECK( NULL == node2->next );
        CHECK( node2 == list->tail );
        mem_release(list);
        mem_release(node3);
    }

    //-------------------------------------------------------------------------
    // Test list_clear function
    //-------------------------------------------------------------------------
    TEST(Verify_list_clear_does_nothing_for_an_empty_list)
    {
        list_t* list = list_new();
        list_clear(list);
        CHECK( NULL == list->head );
        CHECK( NULL == list->tail );
        mem_release(list);
    }

    TEST(Verify_list_clear_clears_a_list_of_length_1)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_front(list,mem_box(0x1234));
        mem_retain(node1);
        list_clear(list);
        CHECK( 1 == mem_num_references(node1) );
        CHECK( NULL == node1->prev );
        CHECK( NULL == node1->next );
        CHECK( NULL == list->head );
        CHECK( NULL == list->tail );
        mem_release(node1);
        mem_release(list);
    }

    TEST(Verify_list_clear_clears_a_list_of_length_2)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_front(list,mem_box(0x1234));
        list_node_t* node2 = list_push_front(list,mem_box(0x4321));
        mem_retain(node1);
        mem_retain(node2);
        list_clear(list);
        CHECK( 1 == mem_num_references(node1) );
        CHECK( NULL == node1->prev );
        CHECK( NULL == node1->next );
        CHECK( 1 == mem_num_references(node2) );
        CHECK( NULL == node2->prev );
        CHECK( NULL == node2->next );
        CHECK( NULL == list->head );
        CHECK( NULL == list->tail );
        mem_release(node1);
        mem_release(node2);
        mem_release(list);
    }

    TEST(Verify_list_clear_clears_a_list_of_length_3)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_front(list,mem_box(0x1234));
        list_node_t* node2 = list_push_front(list,mem_box(0x8888));
        list_node_t* node3 = list_push_front(list,mem_box(0x4321));
        mem_retain(node1);
        mem_retain(node2);
        mem_retain(node3);
        list_clear(list);
        CHECK( 1 == mem_num_references(node1) );
        CHECK( NULL == node1->prev );
        CHECK( NULL == node1->next );
        CHECK( 1 == mem_num_references(node2) );
        CHECK( NULL == node2->prev );
        CHECK( NULL == node2->next );
        CHECK( 1 == mem_num_references(node3) );
        CHECK( NULL == node3->prev );
        CHECK( NULL == node3->next );
        CHECK( NULL == list->head );
        CHECK( NULL == list->tail );
        mem_release(node1);
        mem_release(node2);
        mem_release(node3);
        mem_release(list);
    }
}
