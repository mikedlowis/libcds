// Unit Test Framework Includes
#include "test.h"

// File To Test
#include "map.h"
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
TEST_SUITE(Map) {
    //-------------------------------------------------------------------------
    // Test map_new function
    //-------------------------------------------------------------------------
    TEST(Verify_map_new)
    {
        map_t* map = map_new(cmp_new(NULL, cmp_int), hash_int);
        mem_release(map);
    }

    //-------------------------------------------------------------------------
    // Test map_has_key function
    //-------------------------------------------------------------------------
    TEST(Verify_map_has_key_should_return_true_if_the_item_is_in_the_map)
    {
        map_t* map = map_new(cmp_new(NULL, cmp_int), hash_int);
        void* boxed_val = mem_box(42);
        map_insert(map, boxed_val, mem_retain(boxed_val));
        CHECK(map_size(map) == 1);
        CHECK(map_has_key(map, boxed_val));
        mem_release(map);
    }

    TEST(Verify_map_has_key_should_return_false_if_the_item_is_not_in_the_map)
    {
        map_t* map = map_new(cmp_new(NULL, cmp_int), hash_int);
        void* lup_val = mem_box(43);
        void* box_val = mem_box(42);
        map_insert(map, box_val, mem_retain(box_val));
        CHECK(map_size(map) == 1);
        CHECK(!map_has_key(map, lup_val));
        mem_release(map);
        mem_release(lup_val);
    }

    //-------------------------------------------------------------------------
    // Test map_insert function
    //-------------------------------------------------------------------------
    TEST(Verify_map_insert_multiple_times_replaces_the_associated_value_with_the_new_value)
    {
        map_t* map = map_new(cmp_new(NULL, cmp_int), hash_int);
        void* lup_val = mem_box(42);
        void* box_val = mem_box(43);
        map_insert(map, lup_val, mem_retain(lup_val));
        map_insert(map, mem_retain(lup_val), box_val);
        CHECK(map_size(map) == 1);
        CHECK(map_has_key(map, lup_val));
        mem_release(map);
    }

    TEST(Verify_map_insert_a_value_less_than_an_existing_value)
    {
        map_t* map = map_new(cmp_new(NULL, cmp_int), hash_int);
        void* box_val1 = mem_box(43);
        void* box_val2 = mem_box(42);
        map_insert(map, box_val1, mem_retain(box_val1));
        map_insert(map, box_val2, mem_retain(box_val2));
        CHECK(map_size(map) == 2);
        CHECK(map_has_key(map, box_val2));
        mem_release(map);
    }

    TEST(Verify_map_insert_a_value_greater_than_an_existing_value)
    {
        map_t* map = map_new(cmp_new(NULL, cmp_int), hash_int);
        void* box_val1 = mem_box(42);
        void* box_val2 = mem_box(43);
        map_insert(map, box_val1, mem_retain(box_val1));
        map_insert(map, box_val2, mem_retain(box_val2));
        CHECK(map_size(map) == 2);
        CHECK(map_has_key(map, box_val2));
        mem_release(map);
    }

    //-------------------------------------------------------------------------
    // Test map_delete function
    //-------------------------------------------------------------------------
    TEST(Verify_map_delete_deletes_the_item_from_the_map)
    {
        map_t* map = map_new(cmp_new(NULL, cmp_int), hash_int);
        void* del_val = mem_box(42);
        CHECK(map_size(map) == 0);
        map_insert(map, mem_retain(del_val), mem_retain(del_val));
        CHECK(map_size(map) == 1);
        map_delete(map, del_val);
        CHECK(map_size(map) == 0);
        mem_release(map);
        mem_release(del_val);
    }
}
