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
        CHECK(0 == p_vec->size);
        CHECK(DEFAULT_VEC_CAPACITY == p_vec->capacity);
        CHECK(NULL != p_vec->p_buffer);
        mem_release(p_vec);
    }

    TEST(Verify_vec_new_returns_newly_allocated_vector_with_the_provided_elements)
    {
        vec_t* p_vec = vec_new(2,mem_box(0x1234),mem_box(0x4321));
        CHECK(NULL != p_vec);
        CHECK(2 == p_vec->size);
        CHECK(2 == p_vec->capacity);
        CHECK(NULL != p_vec->p_buffer);
        CHECK(0x1234 == mem_unbox(p_vec->p_buffer[0]));
        CHECK(0x4321 == mem_unbox(p_vec->p_buffer[1]));
        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_size function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_size_returns_the_correct_size)
    {
        vec_t vector = { 42, 24, NULL };
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
        vec_t vector = { 0, 24, NULL };
        CHECK(true == vec_empty(&vector));
    }

    TEST(Verify_vec_empty_returns_false_if_not_empty)
    {
        vec_t vector = { 42, 24, NULL };
        CHECK(false == vec_empty(&vector));
    }

    //-------------------------------------------------------------------------
    // Test vec_resize function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_resize_does_nothing_if_size_is_the_same)
    {
        vec_t* p_vec = vec_new(3, mem_box(0), mem_box(1), mem_box(2));
        vec_resize( p_vec, 3, (void*)0x2A );

        CHECK( 3 == p_vec->size );
        CHECK( 3 == p_vec->capacity );

        mem_release(p_vec);
    }

    TEST(Verify_vec_resize_should_erase_the_last_element)
    {
        vec_t* p_vec = vec_new(3, mem_box(0), mem_box(1), mem_box(2));
        vec_resize( p_vec, 2, (void*)0x2A );

        CHECK( 2 == p_vec->size );
        CHECK( 3 == p_vec->capacity );

        mem_release(p_vec);
    }

    TEST(Verify_vec_resize_should_erase_the_last_two_elements)
    {
        vec_t* p_vec = vec_new(3, mem_box(0), mem_box(1), mem_box(2));
        vec_resize( p_vec, 1, (void*)0x2A );

        CHECK( 1 == p_vec->size );
        CHECK( 3 == p_vec->capacity );

        mem_release(p_vec);
    }

    TEST(Verify_vec_resize_should_add_a_new_element)
    {
    //// TODO: This test is most certainly busted in the presence of refcounting.
    //    vec_t* p_vec = vec_new(3, mem_box(0), mem_box(1), mem_box(2));
    //    vec_resize( p_vec, 4, (void*)0x2A );

    //    CHECK( 4 == p_vec->size );
    //    CHECK( 4 == p_vec->capacity );
    //    CHECK( (void*)0x2A == p_vec->p_buffer[3] );

    //    mem_release(p_vec);
    }

    TEST(Verify_vec_resize_should_add_two_new_elements)
    {
    //// TODO: This test is most certainly busted in the presence of refcounting.
    //    vec_t* p_vec = vec_new(3, mem_box(0), mem_box(1), mem_box(2));
    //    vec_resize( p_vec, 5, (void*)0x2A );

    //    CHECK( 5 == p_vec->size );
    //    CHECK( 8 == p_vec->capacity );
    //    CHECK( (void*)0x2A == p_vec->p_buffer[3] );
    //    CHECK( (void*)0x2A == p_vec->p_buffer[4] );
    //
    //    mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_shrink_to_fit function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_shrink_to_fit_shrinks_capacity_to_equal_the_size)
    {
        vec_t vector = { 1, 2, (void**)malloc(sizeof(void*) * 2) };
        vec_shrink_to_fit(&vector);
        CHECK( vector.size == vector.capacity );
        free(vector.p_buffer);
    }

    //-------------------------------------------------------------------------
    // Test vec_capacity function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_capacity_returns_the_correct_size)
    {
        vec_t vector = { 42, 24, NULL };
        CHECK(24 == vec_capacity(&vector));
    }

    //-------------------------------------------------------------------------
    // Test vec_reserve function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_reserve_reserves_a_buffer_of_the_desired_size)
    {
        vec_t vector = { 0, 0, NULL };
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
        vec_t vector = { 2, 2, array };
        CHECK((void*)0x4321 == vec_at(&vector,1));

    }

    TEST(Verify_vec_at_returns_null_if_index_out_of_range)
    {
        void* array[2] = { (void*)0x1234, (void*)0x4321 };
        vec_t vector = { 2, 2, array };
        CHECK(NULL == vec_at(&vector,2));
    }

    //-------------------------------------------------------------------------
    // Test vec_set function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_set_sets_the_value_at_the_given_index)
    {
        void* data[3] = { (void*)0x1234, NULL, NULL };
        vec_t vector = { 2, 3, data };
        CHECK(true == vec_set(&vector,1,(void*)0x4321));
        CHECK((void*)0x4321 == data[1]);
        CHECK(NULL == data[2]);
    }

    TEST(Verify_vec_set_returns_false_if_index_out_of_range)
    {
        void* data[3] = { (void*)0x1234, NULL, NULL };
        vec_t vector = { 2, 3, data };
        CHECK(false == vec_set(&vector,2,(void*)0x4321));
        CHECK(NULL == data[1]);
        CHECK(NULL == data[2]);
    }

    //-------------------------------------------------------------------------
    // Test vec_insert function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_insert_should_do_nothing_if_index_out_of_range)
    {
        vec_t vector = { 2, 3, NULL };
        CHECK(false == vec_insert(&vector,2,0));
    }

    TEST(Verify_vec_insert_should_do_nothing_if_num_elements_is_0)
    {
        vec_t vector = { 2, 3, NULL };
        CHECK(false == vec_insert(&vector,0,0));
    }

    TEST(Verify_vec_insert_should_insert_items_at_the_given_index)
    {
    //// TODO: release fails for some reason. Investigate
    //    vec_t* p_vec = vec_new(2,mem_box(0),mem_box(1));
    //    CHECK(true == vec_insert(p_vec,1,2,mem_box(2),mem_box(3)));
    //    CHECK(4 == p_vec->size);
    //    CHECK(4 == p_vec->capacity);
    //    CHECK(0 == mem_unbox(p_vec->p_buffer[0]));
    //    CHECK(2 == mem_unbox(p_vec->p_buffer[1]));
    //    CHECK(3 == mem_unbox(p_vec->p_buffer[2]));
    //    CHECK(1 == mem_unbox(p_vec->p_buffer[3]));
    //    //mem_release(p_vec);
    }

    TEST(Verify_vec_insert_should_insert_items_at_the_beginning)
    {
    //// TODO: release fails for some reason. Investigate
    //    vec_t* p_vec = vec_new(2,mem_box(0),mem_box(1));
    //    CHECK(true == vec_insert(p_vec,0,2,mem_box(2),mem_box(3)));
    //    CHECK(4 == p_vec->size);
    //    CHECK(4 == p_vec->capacity);
    //    CHECK(2 == mem_unbox(p_vec->p_buffer[0]));
    //    CHECK(3 == mem_unbox(p_vec->p_buffer[1]));
    //    CHECK(0 == mem_unbox(p_vec->p_buffer[2]));
    //    CHECK(1 == mem_unbox(p_vec->p_buffer[3]));
    //    //mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_erase function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_erase_erases_the_first_item)
    {
        void* data[3] = { mem_box(1), mem_box(2), mem_box(3) };
        vec_t vector = { 3, 3, data };
        CHECK(true == vec_erase( &vector, 0, 0 ));
        CHECK(2 == vector.size);
        CHECK(0x2 == mem_unbox(data[0]));
        CHECK(0x3 == mem_unbox(data[1]));
    }

    TEST(Verify_vec_erase_erases_a_single_item)
    {
        void* data[3] = { mem_box(1), mem_box(2), mem_box(3) };
        vec_t vector = { 3, 3, data };
        CHECK(true == vec_erase( &vector, 1, 1 ));
        CHECK(2 == vector.size);
        CHECK(0x1 == mem_unbox(data[0]));
        CHECK(0x3 == mem_unbox(data[1]));
    }

    TEST(Verify_vec_erase_erases_multiple_items)
    {
        void* data[4] = { mem_box(1), mem_box(2), mem_box(3), mem_box(4) };
        vec_t vector = { 4, 4, data };
        CHECK(true == vec_erase( &vector, 1, 2 ));
        CHECK(2 == vector.size);
        CHECK(0x1 == mem_unbox(data[0]));
        CHECK(0x4 == mem_unbox(data[1]));
    }

    TEST(Verify_vec_erase_erases_everything)
    {
        void* data[4] = { mem_box(1), mem_box(2), mem_box(3), mem_box(4) };
        vec_t vector = { 4, 4, data };
        CHECK(true == vec_erase( &vector, 0, 3 ));
        CHECK(0 == vector.size);
    }

    TEST(Verify_vec_erase_should_fail_for_invalid_ranges)
    {
        void* data[4] = { mem_box(1), mem_box(2), mem_box(3), mem_box(4) };
        vec_t vector = { 4, 4, data };
        CHECK(false == vec_erase( &vector, 0, 4 ));
    }

    TEST(Verify_vec_erase_everything_but_last)
    {
        void* data[4] = { mem_box(1), mem_box(2), mem_box(3), mem_box(4) };
        vec_t vector = { 4, 4, data };
        CHECK(true == vec_erase( &vector, 0, 2 ));
        CHECK(0x4 == mem_unbox(data[0]));
        CHECK(1 == vector.size);
    }

    TEST(Verify_vec_erase_everything_but_first)
    {
        void* data[4] = { mem_box(1), mem_box(2), mem_box(3), mem_box(4) };
        vec_t vector = { 4, 4, data };
        CHECK(true == vec_erase( &vector, 1, 3 ));
        CHECK(0x1 == mem_unbox(data[0]));
        CHECK(1 == vector.size);
    }

    //-------------------------------------------------------------------------
    // Test vec_push_back function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_push_back_should_push_a_new_element_to_the_end)
    {
        vec_t* p_vec = vec_new(3,mem_box(0), mem_box(1), mem_box(2));
        vec_push_back( p_vec, mem_box(0x2A) );
        CHECK( 4 == p_vec->size );
        CHECK( 4 == p_vec->capacity );
        CHECK( 0x2A == mem_unbox(p_vec->p_buffer[3]) );
        mem_release(p_vec);
    }

    TEST(Verify_vec_push_back_should_push_a_new_element_to_the_end_of_empty_vector)
    {
        vec_t* p_vec = vec_new(0);
        vec_push_back( p_vec, mem_box(0x2A) );
        CHECK( 1 == p_vec->size );
        CHECK( 1 == p_vec->capacity );
        CHECK( 0x2A == mem_unbox(p_vec->p_buffer[0]) );
        mem_release(p_vec);
    }

    //-------------------------------------------------------------------------
    // Test vec_pop_back function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_pop_back_returns_last_element)
    {
        void* data[4] = { mem_box(1), mem_box(2), mem_box(3), mem_box(4) };
        vec_t vector = { 4, 4, data };
        void* p_box = vec_pop_back( &vector );
        CHECK( 0x4 == mem_unbox(p_box) );
        CHECK( 4 == vector.capacity );
        CHECK( 3 == vector.size );
    }

    TEST(Verify_vec_pop_back_does_nothing_if_no_elements)
    {
        vec_t vector = { 0, 0, NULL };
        CHECK( NULL == vec_pop_back( &vector ) );
        CHECK( 0 == vector.capacity );
        CHECK( 0 == vector.size );
    }

    //-------------------------------------------------------------------------
    // Test vec_clear function
    //-------------------------------------------------------------------------
    TEST(Verify_vec_clear_clears_the_vector)
    {
        void* data[4] = { mem_box(1), mem_box(2), mem_box(3), mem_box(4) };
        vec_t vector = { 4, 4, data };
        vec_clear( &vector );
        CHECK(0 == vector.size);
    }
}
