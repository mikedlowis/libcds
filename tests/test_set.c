// Unit Test Framework Includes
#include "test.h"

// File To Test
#include "set.h"
#include "murmur3.h"

static void test_setup(void) { }

static uint32_t hash_int(void* obj) {
    intptr_t val = mem_unbox(obj);
    return murmur3_32((uint8_t*)&val, sizeof(intptr_t));
}

static int cmp_int(void* env, void* obja, void* objb) {
    uintptr_t inta = mem_unbox(obja);
    uintptr_t intb = mem_unbox(objb);
    (void)env;
    if (inta < intb)
        return -1;
    else if (intb < inta)
        return 1;
    else
        return 0;
}

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
TEST_SUITE(Set) {
    //-------------------------------------------------------------------------
    // Test set_new function
    //-------------------------------------------------------------------------
    TEST(Verify_set_new)
    {
        set_t* set = set_new(cmp_new(NULL, cmp_int), hash_int);
        mem_release(set);
    }

    //-------------------------------------------------------------------------
    // Test set_contains function
    //-------------------------------------------------------------------------
    TEST(Verify_set_contains_should_return_true_if_the_item_is_in_the_set)
    {
        set_t* set = set_new(cmp_new(NULL, cmp_int), hash_int);
        void* boxed_val = mem_box(42);
        set_insert(set, boxed_val);
        CHECK(set_size(set) == 1);
        CHECK(set_contains(set, boxed_val));
        mem_release(set);
    }

    TEST(Verify_set_contains_should_return_false_if_the_item_is_not_in_the_set)
    {
        set_t* set = set_new(cmp_new(NULL, cmp_int), hash_int);
        void* lup_val = mem_box(43);
        set_insert(set, mem_box(42));
        CHECK(set_size(set) == 1);
        CHECK(!set_contains(set, lup_val));
        mem_release(set);
        mem_release(lup_val);
    }

    //-------------------------------------------------------------------------
    // Test set_insert function
    //-------------------------------------------------------------------------
    TEST(Verify_set_insert_multiple_times_with_the_same_value_only_inserts_once)
    {
        set_t* set = set_new(cmp_new(NULL, cmp_int), hash_int);
        void* lup_val = mem_box(42);
        set_insert(set, mem_box(42));
        set_insert(set, mem_box(42));
        CHECK(set_size(set) == 1);
        CHECK(set_contains(set, lup_val));
        mem_release(set);
        mem_release(lup_val);
    }

    TEST(Verify_set_insert_a_value_less_than_an_existing_value)
    {
        set_t* set = set_new(cmp_new(NULL, cmp_int), hash_int);
        void* lup_val = mem_box(41);
        set_insert(set, mem_box(42));
        set_insert(set, mem_box(41));
        CHECK(set_size(set) == 2);
        CHECK(set_contains(set, lup_val));
        mem_release(set);
        mem_release(lup_val);
    }

    TEST(Verify_set_insert_a_value_greater_than_an_existing_value)
    {
        set_t* set = set_new(cmp_new(NULL, cmp_int), hash_int);
        void* lup_val = mem_box(42);
        set_insert(set, mem_box(41));
        set_insert(set, mem_box(42));
        CHECK(set_size(set) == 2);
        CHECK(set_contains(set, lup_val));
        mem_release(set);
        mem_release(lup_val);
    }

    //-------------------------------------------------------------------------
    // Test set_delete function
    //-------------------------------------------------------------------------
    TEST(Verify_set_delete_deletes_the_item_from_the_set)
    {
        set_t* set = set_new(cmp_new(NULL, cmp_int), hash_int);
        void* del_val = mem_box(42);
        CHECK(set_size(set) == 0);
        set_insert(set, mem_box(42));
        CHECK(set_size(set) == 1);
        set_delete(set, del_val);
        CHECK(set_size(set) == 0);
        mem_release(set);
        mem_release(del_val);
    }
}
