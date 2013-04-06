// Unit Test Framework Includes
#include "UnitTest++.h"
#include <cstdlib>
#include <iostream>

// File To Test
#include "vec.h"

using namespace UnitTest;

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
namespace {
    //-------------------------------------------------------------------------
    // Test vec_new function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_new_returns_newly_allocated_vector_with_default_capacity)
    {
        vec_t* p_vec = vec_new(true,0);
        CHECK(NULL != p_vec);
        CHECK(true == p_vec->own_contents);
        CHECK(0 == p_vec->size);
        CHECK(DEFAULT_VEC_CAPACITY == p_vec->capacity);
        CHECK(NULL != p_vec->p_buffer);
        vec_free(p_vec);
    }

    TEST(Verify_vec_new_returns_newly_allocated_vector_with_the_provided_elements)
    {
        vec_t* p_vec = vec_new(false,2,(void*)0x1234,(void*)0x4321);
        CHECK(NULL != p_vec);
        CHECK(false == p_vec->own_contents);
        CHECK(2 == p_vec->size);
        CHECK(2 == p_vec->capacity);
        CHECK(NULL != p_vec->p_buffer);
        CHECK((void*)0x1234 == p_vec->p_buffer[0]);
        CHECK((void*)0x4321 == p_vec->p_buffer[1]);
        vec_free(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_free function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_free_frees_the_vector_and_contents)
    {
        vec_t* p_vec = vec_new(true,0);
        vec_free(p_vec);
    }

    TEST(Verify_vec_free_frees_the_vector)
    {
        vec_t* p_vec = vec_new(false,0);
        vec_free(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_size function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_size_returns_the_correct_size)
    {
        vec_t vector = { false, 42, 24, NULL };
        CHECK(42 == vec_size(&vector));
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
        vec_t vector = { false, 0, 24, NULL };
        CHECK(true == vec_empty(&vector));
    }

    TEST(Verify_vec_empty_returns_false_if_not_empty)
    {
        vec_t vector = { false, 42, 24, NULL };
        CHECK(false == vec_empty(&vector));
    }

    //-------------------------------------------------------------------------
    // Test vec_resize function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_resize_does_nothing_if_size_is_the_same)
    {
        vec_t* p_vec = vec_new(false,3,0,1,2);
        vec_resize( p_vec, 3, (void*)0x2A );

        CHECK( false == p_vec->own_contents );
        CHECK( 3 == p_vec->size );
        CHECK( 3 == p_vec->capacity );

        vec_free( p_vec );
    }

    TEST(Verify_vec_resize_should_erase_the_last_element)
    {
        vec_t* p_vec = vec_new(false,3,0,1,2);
        vec_resize( p_vec, 2, (void*)0x2A );

        CHECK( false == p_vec->own_contents );
        CHECK( 2 == p_vec->size );
        CHECK( 3 == p_vec->capacity );

        vec_free( p_vec );
    }

    TEST(Verify_vec_resize_should_erase_the_last_two_elements)
    {
        vec_t* p_vec = vec_new(false,3,0,1,2);
        vec_resize( p_vec, 1, (void*)0x2A );

        CHECK( false == p_vec->own_contents );
        CHECK( 1 == p_vec->size );
        CHECK( 3 == p_vec->capacity );

        vec_free( p_vec );
    }

    TEST(Verify_vec_resize_should_add_a_new_element)
    {
        vec_t* p_vec = vec_new(false,3,0,1,2);
        vec_resize( p_vec, 4, (void*)0x2A );

        CHECK( false == p_vec->own_contents );
        CHECK( 4 == p_vec->size );
        CHECK( 4 == p_vec->capacity );
        CHECK( (void*)0x2A == p_vec->p_buffer[3] );

        vec_free( p_vec );
    }

    TEST(Verify_vec_resize_should_add_two_new_elements)
    {
        vec_t* p_vec = vec_new(false,3,0,1,2);
        vec_resize( p_vec, 5, (void*)0x2A );

        CHECK( false == p_vec->own_contents );
        CHECK( 5 == p_vec->size );
        CHECK( 5 == p_vec->capacity );
        CHECK( (void*)0x2A == p_vec->p_buffer[3] );
        CHECK( (void*)0x2A == p_vec->p_buffer[4] );

        vec_free( p_vec );
    }

    //-------------------------------------------------------------------------
    // Test vec_shrink_to_fit function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_shrink_to_fit_shrinks_capacity_to_equal_the_size)
    {
        vec_t vector = { false, 1, 2, (void**)malloc(sizeof(void*) * 2) };
        vec_shrink_to_fit(&vector);
        CHECK( vector.size == vector.capacity );
        free( vector.p_buffer );
    }

    //-------------------------------------------------------------------------
    // Test vec_capacity function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_capacity_returns_the_correct_size)
    {
        vec_t vector = { false, 42, 24, NULL };
        CHECK(24 == vec_capacity(&vector));
    }

    //-------------------------------------------------------------------------
    // Test vec_reserve function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_reserve_reserves_a_buffer_of_the_desired_size)
    {
        vec_t vector = { false, 0, 0, NULL };
        vec_reserve(&vector,5);
        CHECK( 5 == vector.capacity );
        free( vector.p_buffer );
    }

    //-------------------------------------------------------------------------
    // Test vec_at function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_at_returns_an_item_at_the_provided_index)
    {
        void* array[2] = { (void*)0x1234, (void*)0x4321 };
        vec_t vector = { false, 2, 2, array };
        CHECK((void*)0x4321 == vec_at(&vector,1));

    }

    TEST(Verify_vec_at_returns_null_if_index_out_of_range)
    {
        void* array[2] = { (void*)0x1234, (void*)0x4321 };
        vec_t vector = { false, 2, 2, array };
        CHECK(NULL == vec_at(&vector,2));
    }

    //-------------------------------------------------------------------------
    // Test vec_set function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_set_sets_the_value_at_the_given_index)
    {
        void* data[3] = { (void*)0x1234, NULL, NULL };
        vec_t vector = { false, 2, 3, data };
        CHECK(true == vec_set(&vector,1,(void*)0x4321));
        CHECK((void*)0x4321 == data[1]);
        CHECK(NULL == data[2]);
    }

    TEST(Verify_vec_set_returns_false_if_index_out_of_range)
    {
        void* data[3] = { (void*)0x1234, NULL, NULL };
        vec_t vector = { false, 2, 3, data };
        CHECK(false == vec_set(&vector,2,(void*)0x4321));
        CHECK(NULL == data[1]);
        CHECK(NULL == data[2]);
    }

    //-------------------------------------------------------------------------
    // Test vec_insert function
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // Test vec_erase function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_erase_erases_a_single_item)
    {
        void* data[3] = { (void*)0x1, (void*)0x2, (void*)0x3 };
        vec_t vector = { false, 3, 3, data };
        CHECK(true == vec_erase( &vector, 1, 1 ));
        CHECK(2 == vector.size);
        CHECK((void*)0x1 == data[0]);
        CHECK((void*)0x3 == data[1]);
    }

    TEST(Verify_vec_erase_erases_a_multiple_items)
    {
        void* data[4] = { (void*)0x1, (void*)0x2, (void*)0x3, (void*)0x4 };
        vec_t vector = { false, 4, 4, data };
        CHECK(true == vec_erase( &vector, 1, 2 ));
        CHECK(2 == vector.size);
        CHECK((void*)0x1 == data[0]);
        CHECK((void*)0x4 == data[1]);
    }

    TEST(Verify_vec_erase_erases_everything)
    {
        void* data[4] = { (void*)0x1, (void*)0x2, (void*)0x3, (void*)0x4 };
        vec_t vector = { false, 4, 4, data };
        CHECK(true == vec_erase( &vector, 0, 3 ));
        CHECK(0 == vector.size);
    }

    TEST(Verify_vec_erase_should_fail_for_invalid_ranges)
    {
        void* data[4] = { (void*)0x1, (void*)0x2, (void*)0x3, (void*)0x4 };
        vec_t vector = { false, 4, 4, data };
        CHECK(false == vec_erase( &vector, 0, 4 ));
    }

    TEST(Verify_vec_erase_everything_but_last)
    {
        void* data[4] = { (void*)0x1, (void*)0x2, (void*)0x3, (void*)0x4 };
        vec_t vector = { false, 4, 4, data };
        CHECK(true == vec_erase( &vector, 0, 2 ));
        CHECK((void*)0x4 == data[0]);
        CHECK(1 == vector.size);
    }

    TEST(Verify_vec_erase_everything_but_first)
    {
        void* data[4] = { (void*)0x1, (void*)0x2, (void*)0x3, (void*)0x4 };
        vec_t vector = { false, 4, 4, data };
        CHECK(true == vec_erase( &vector, 1, 3 ));
        CHECK((void*)0x1 == data[0]);
        CHECK(1 == vector.size);
    }

    //-------------------------------------------------------------------------
    // Test vec_push_back function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_push_back_should_push_a_new_element_to_the_end)
    {
        vec_t* p_vec = vec_new(false,3,0,1,2);
        vec_push_back( p_vec, (void*)0x2A );

        CHECK( false == p_vec->own_contents );
        CHECK( 4 == p_vec->size );
        CHECK( 4 == p_vec->capacity );
        CHECK( (void*)0x2A == p_vec->p_buffer[3] );

        vec_free( p_vec );
    }

    TEST(Verify_vec_push_back_should_push_a_new_element_to_the_end_of_empty_vector)
    {
        vec_t* p_vec = vec_new(false,0);
        vec_push_back( p_vec, (void*)0x2A );

        CHECK( false == p_vec->own_contents );
        CHECK( 1 == p_vec->size );
        CHECK( 1 == p_vec->capacity );
        CHECK( (void*)0x2A == p_vec->p_buffer[0] );

        vec_free( p_vec );
    }

    //-------------------------------------------------------------------------
    // Test vec_pop_back function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_pop_back_returns_last_element)
    {
        void* data[4] = { (void*)0x1, (void*)0x2, (void*)0x3, (void*)0x4 };
        vec_t vector = { false, 4, 4, data };
        CHECK( (void*)0x4 == vec_pop_back( &vector ) );
        CHECK( 4 == vector.capacity );
        CHECK( 3 == vector.size );
    }

    TEST(Verify_vec_pop_back_does_nothing_if_no_elements)
    {
        vec_t vector = { false, 0, 0, NULL };
        CHECK( NULL == vec_pop_back( &vector ) );
        CHECK( 0 == vector.capacity );
        CHECK( 0 == vector.size );
    }

    //-------------------------------------------------------------------------
    // Test vec_clear function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_clear_clears_the_vector)
    {
        void* data[4] = { (void*)0x1, (void*)0x2, (void*)0x3, (void*)0x4 };
        vec_t vector = { false, 4, 4, data };
        vec_clear( &vector );
        CHECK(0 == vector.size);
    }
}
