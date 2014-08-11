// Unit Test Framework Includes
#include "test.h"
#include "mem.h"
#include <stdlib.h>

// File To Test
#include "vec.h"

static void test_setup(void) { }

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
TEST_SUITE(Vector) {
    //-------------------------------------------------------------------------
    // Test vec_new function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_new_returns_newly_allocated_vector_with_default_capacity)
    {
        vec_t* p_vec = vec_new(0);
        CHECK(NULL != p_vec);
        CHECK(0 == vec_size(p_vec));
        CHECK(DEFAULT_VEC_CAPACITY == vec_capacity(p_vec));
        mem_release(p_vec);
    }

    TEST(Verify_vec_new_returns_newly_allocated_vector_with_the_provided_elements)
    {
        vec_t* p_vec = vec_new(2,mem_box(0x1234),mem_box(0x4321));
        CHECK(NULL != p_vec);
        CHECK(2 == vec_size(p_vec));
        CHECK(2 == vec_capacity(p_vec));
        CHECK(0x1234 == mem_unbox(vec_at(p_vec,0)));
        CHECK(0x4321 == mem_unbox(vec_at(p_vec,1)));
        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_size function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_size_returns_the_correct_size)
    {
        vec_t* p_vec = vec_new(1, mem_box(0x1234));
        CHECK(1 == vec_size(p_vec));
        vec_push_back(p_vec, mem_box(0x1234));
        CHECK(2 == vec_size(p_vec));
        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_max_size function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_max_size_returns_the_correct_size)
    {
        CHECK((size_t)-1 == vec_max_size());
    }

    //-------------------------------------------------------------------------
    // Test vec_empty function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_empty_returns_true_if_empty)
    {
        vec_t* p_vec = vec_new(0);
        CHECK(true == vec_empty(p_vec));
        mem_release(p_vec);
    }

    TEST(Verify_vec_empty_returns_false_if_not_empty)
    {
        vec_t* p_vec = vec_new(1, mem_box(0x1234));
        CHECK(false == vec_empty(p_vec));
        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_resize function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_resize_does_nothing_if_size_is_the_same)
    {
        vec_t* p_vec = vec_new(3, mem_box(0), mem_box(1), mem_box(2));
        vec_resize( p_vec, 3, (void*)0x2A );

        CHECK( 3 == vec_size(p_vec) );
        CHECK( 3 == vec_capacity(p_vec) );

        mem_release(p_vec);
    }

    TEST(Verify_vec_resize_should_erase_the_last_element)
    {
        vec_t* p_vec = vec_new(3, mem_box(0), mem_box(1), mem_box(2));
        vec_resize( p_vec, 2, (void*)0x2A );

        CHECK( 2 == vec_size(p_vec) );
        CHECK( 3 == vec_capacity(p_vec) );

        mem_release(p_vec);
    }

    TEST(Verify_vec_resize_should_erase_the_last_two_elements)
    {
        vec_t* p_vec = vec_new(3, mem_box(0), mem_box(1), mem_box(2));
        vec_resize( p_vec, 1, (void*)0x2A );

        CHECK( 1 == vec_size(p_vec) );
        CHECK( 3 == vec_capacity(p_vec) );

        mem_release(p_vec);
    }

    TEST(Verify_vec_resize_should_add_a_new_element)
    {
        vec_t* p_vec = vec_new(3, mem_box(0), mem_box(1), mem_box(2));
        vec_resize( p_vec, 4, mem_box(0x2A) );

        CHECK( 4 == vec_size(p_vec) );
        CHECK( 8 == vec_capacity(p_vec) );
        CHECK( 0x2A == mem_unbox(vec_at(p_vec,3)) );

        mem_release(p_vec);
    }

    TEST(Verify_vec_resize_should_add_two_new_elements)
    {
        vec_t* p_vec = vec_new(3, mem_box(0), mem_box(1), mem_box(2));
        vec_resize( p_vec, 5, mem_box(0x2A) );

        CHECK( 5 == vec_size(p_vec) );
        CHECK( 8 == vec_capacity(p_vec) );
        CHECK( 0x2A == mem_unbox(vec_at(p_vec,3)) );
        CHECK( 0x2A == mem_unbox(vec_at(p_vec,4)) );

        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_shrink_to_fit function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_shrink_to_fit_shrinks_capacity_to_equal_the_size)
    {
        vec_t* p_vec = vec_new(3, mem_box(0), mem_box(1), mem_box(2));
        vec_resize( p_vec, 5, mem_box(0x2A) );
        CHECK( 5 == vec_size(p_vec) );
        CHECK( 8 == vec_capacity(p_vec) );
        vec_shrink_to_fit(p_vec);
        CHECK( 5 == vec_size(p_vec) );
        CHECK( 5 == vec_capacity(p_vec) );
        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_capacity function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_capacity_returns_the_correct_size)
    {
        vec_t* p_vec = vec_new(0);
        CHECK( 8 == vec_capacity(p_vec) );
        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_reserve function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_reserve_reserves_a_buffer_of_the_desired_size)
    {
        vec_t* p_vec = vec_new(0);
        vec_reserve(p_vec, 15);
        CHECK( 15 == vec_capacity(p_vec) );
        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_at function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_at_returns_an_item_at_the_provided_index)
    {
        vec_t* p_vec = vec_new(2, mem_box(0x1234), mem_box(0x4321));
        CHECK(0x4321 == mem_unbox(vec_at(p_vec,1)));
        mem_release(p_vec);
    }

    TEST(Verify_vec_at_returns_null_if_index_out_of_range)
    {
        vec_t* p_vec = vec_new(2, mem_box(0x1234), mem_box(0x4321));
        CHECK(NULL == vec_at(p_vec,2));
        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_set function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_set_sets_the_value_at_the_given_index)
    {
        vec_t* p_vec = vec_new(2, mem_box(0x1234), mem_box(0x4321));
        CHECK(true == vec_set(p_vec, 1, mem_box(0x1234)));
        CHECK(0x1234 == mem_unbox(vec_at(p_vec,1)));
        mem_release(p_vec);
    }

    TEST(Verify_vec_set_returns_false_if_index_out_of_range)
    {
        vec_t* p_vec = vec_new(2, mem_box(0x1234), mem_box(0x4321));
        CHECK(false == vec_set(p_vec, 2, mem_box(0x1234)));
        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_insert function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_insert_should_do_nothing_if_index_out_of_range)
    {
        vec_t* p_vec = vec_new(2, mem_box(0x1234), mem_box(0x4321));
        CHECK(false == vec_insert(p_vec, 2, 1, mem_box(0x1234)));
        mem_release(p_vec);
    }

    TEST(Verify_vec_insert_should_do_nothing_if_num_elements_is_0)
    {
        vec_t* p_vec = vec_new(2, mem_box(0x1234), mem_box(0x4321));
        CHECK(true == vec_insert(p_vec, 1, 1, mem_box(0x1234)));
        mem_release(p_vec);
    }

    TEST(Verify_vec_insert_should_insert_items_at_the_given_index)
    {
        vec_t* p_vec = vec_new(2,mem_box(0),mem_box(1));
        CHECK(true == vec_insert(p_vec,1,2,mem_box(2),mem_box(3)));
        CHECK(4 == vec_size(p_vec));
        CHECK(8 == vec_capacity(p_vec));
        CHECK(0 == mem_unbox(vec_at(p_vec,0)));
        CHECK(2 == mem_unbox(vec_at(p_vec,1)));
        CHECK(3 == mem_unbox(vec_at(p_vec,2)));
        CHECK(1 == mem_unbox(vec_at(p_vec,3)));
        mem_release(p_vec);
    }

    TEST(Verify_vec_insert_should_insert_items_at_the_beginning)
    {
        vec_t* p_vec = vec_new(2,mem_box(0),mem_box(1));
        CHECK(true == vec_insert(p_vec,0,2,mem_box(2),mem_box(3)));
        CHECK(4 == vec_size(p_vec));
        CHECK(8 == vec_capacity(p_vec));
        CHECK(2 == mem_unbox(vec_at(p_vec,0)));
        CHECK(3 == mem_unbox(vec_at(p_vec,1)));
        CHECK(0 == mem_unbox(vec_at(p_vec,2)));
        CHECK(1 == mem_unbox(vec_at(p_vec,3)));
        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_erase function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_erase_erases_the_first_item)
    {
        vec_t* p_vec = vec_new(3, mem_box(1), mem_box(2), mem_box(3));
        CHECK(true == vec_erase( p_vec, 0, 0 ));
        CHECK(2 == vec_size(p_vec));
        CHECK(0x2 == mem_unbox(vec_at(p_vec,0)));
        CHECK(0x3 == mem_unbox(vec_at(p_vec,1)));
        mem_release(p_vec);
    }

    TEST(Verify_vec_erase_erases_a_single_item)
    {
        vec_t* p_vec = vec_new(3, mem_box(1), mem_box(2), mem_box(3));
        CHECK(true == vec_erase( p_vec, 1, 1 ));
        CHECK(2 == vec_size(p_vec));
        CHECK(0x1 == mem_unbox(vec_at(p_vec,0)));
        CHECK(0x3 == mem_unbox(vec_at(p_vec,1)));
        mem_release(p_vec);
    }

    TEST(Verify_vec_erase_erases_multiple_items)
    {
        vec_t* p_vec = vec_new(4, mem_box(1), mem_box(2), mem_box(3), mem_box(4));
        CHECK(true == vec_erase( p_vec, 1, 2 ));
        CHECK(2 == vec_size(p_vec));
        CHECK(0x1 == mem_unbox(vec_at(p_vec,0)));
        CHECK(0x4 == mem_unbox(vec_at(p_vec,1)));
        mem_release(p_vec);
    }

    TEST(Verify_vec_erase_erases_everything)
    {
        vec_t* p_vec = vec_new(4, mem_box(1), mem_box(2), mem_box(3), mem_box(4));
        CHECK(true == vec_erase( p_vec, 0, 3 ));
        CHECK(0 == vec_size(p_vec));
        mem_release(p_vec);
    }

    TEST(Verify_vec_erase_should_fail_for_invalid_ranges)
    {
        vec_t* p_vec = vec_new(4, mem_box(1), mem_box(2), mem_box(3), mem_box(4));
        CHECK(false == vec_erase( p_vec, 0, 4 ));
        mem_release(p_vec);
    }

    TEST(Verify_vec_erase_everything_but_last)
    {
        vec_t* p_vec = vec_new(4, mem_box(1), mem_box(2), mem_box(3), mem_box(4));
        CHECK(true == vec_erase( p_vec, 0, 2 ));
        CHECK(0x4 == mem_unbox(vec_at(p_vec,0)));
        CHECK(1 == vec_size(p_vec));
        mem_release(p_vec);
    }

    TEST(Verify_vec_erase_everything_but_first)
    {
        vec_t* p_vec = vec_new(4, mem_box(1), mem_box(2), mem_box(3), mem_box(4));
        CHECK(true == vec_erase( p_vec, 1, 3 ));
        CHECK(0x1 == mem_unbox(vec_at(p_vec,0)));
        CHECK(1 == vec_size(p_vec));
        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_push_back function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_push_back_should_push_a_new_element_to_the_end)
    {
        vec_t* p_vec = vec_new(3,mem_box(0), mem_box(1), mem_box(2));
        vec_push_back( p_vec, mem_box(0x2A) );
        CHECK( 4 == vec_size(p_vec) );
        CHECK( 8 == vec_capacity(p_vec) );
        CHECK( 0x2A == mem_unbox(vec_at(p_vec,3)) );
        mem_release(p_vec);
    }

    TEST(Verify_vec_push_back_should_push_a_new_element_to_the_end_of_empty_vector)
    {
        vec_t* p_vec = vec_new(0);
        vec_push_back( p_vec, mem_box(0x2A) );
        CHECK( 1 == vec_size(p_vec) );
        CHECK( 2 == vec_capacity(p_vec) );
        CHECK( 0x2A == mem_unbox(vec_at(p_vec,0)) );
        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_pop_back function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_pop_back_returns_last_element)
    {
        vec_t* p_vec = vec_new(4, mem_box(1), mem_box(2), mem_box(3), mem_box(4));
        void* p_box = vec_pop_back( p_vec );
        CHECK( 0x4 == mem_unbox(p_box) );
        CHECK( 4 == vec_capacity(p_vec) );
        CHECK( 3 == vec_size(p_vec) );
        mem_release(p_vec);
        mem_release(p_box);
    }

    TEST(Verify_vec_pop_back_does_nothing_if_no_elements)
    {
        vec_t* p_vec = vec_new(0);
        CHECK(NULL == vec_pop_back( p_vec ));
        CHECK(8 == vec_capacity(p_vec));
        CHECK(0 == vec_size(p_vec));
        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_clear function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_clear_clears_the_vector)
    {
        vec_t* p_vec = vec_new(4, mem_box(1), mem_box(2), mem_box(3), mem_box(4));
        vec_clear(p_vec);
        CHECK( 0 == vec_size(p_vec) );
        mem_release(p_vec);
    }
}
