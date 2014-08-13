// Unit Test Framework Includes
#include "test.h"

// File To Test
#include "str.h"

static void test_setup(void) { }

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
TEST_SUITE(String) {
    //-------------------------------------------------------------------------
    // Test str_new function
    //-------------------------------------------------------------------------
    TEST(Verify_str_new_returns_a_new_string)
    {
        str_t* p_str = str_new("foo");
        CHECK(0 == strcmp(str_cstr(p_str), "foo"));
        mem_release(p_str);
    }

    //-------------------------------------------------------------------------
    // Test str_size function
    //-------------------------------------------------------------------------
    TEST(Verify_str_size_returns_the_size_of_the_string)
    {
        str_t* p_str = str_new("foo");
        CHECK(3 == str_size(p_str));
        mem_release(p_str);
    }

    //-------------------------------------------------------------------------
    // Test str_copy function
    //-------------------------------------------------------------------------
    TEST(Verify_str_copy_should_make_an_exact_copy_of_the_string)
    {
        str_t* p_str1 = str_new("foo");
        str_t* p_str2 = str_copy(p_str1);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str1), str_cstr(p_str2)));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    //-------------------------------------------------------------------------
    // Test str_at function
    //-------------------------------------------------------------------------
    TEST(Verify_str_at_should_return_a_char_from_the_string)
    {
        str_t* p_str = str_new("abc");
        CHECK('c' == str_at(p_str,2));
        mem_release(p_str);
    }

    TEST(Verify_str_at_should_return_null_char_if_index_out_of_range)
    {
        str_t* p_str = str_new("abc");
        CHECK('\0' == str_at(p_str,3));
        mem_release(p_str);
    }

    //-------------------------------------------------------------------------
    // Test str_set function
    //-------------------------------------------------------------------------
    TEST(Verify_str_set_should_return_null_if_index_out_of_range)
    {
        str_t* p_str = str_new("abc");
        CHECK(NULL == str_set(p_str,3,'d'));
        mem_release(p_str);
    }

    TEST(Verify_str_set_should_return_a_new_string_with_the_char_at_the_specified_index)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_set(p_str1, 2, 'd');
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str1),"abc"));
        CHECK(0 == strcmp(str_cstr(p_str2),"abd"));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    //-------------------------------------------------------------------------
    // Test str_concat function
    //-------------------------------------------------------------------------
    TEST(Verify_str_concat_should_concat_the_two_strings_and_return_a_new_string)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_new("def");
        str_t* p_str3 = str_concat(p_str1, p_str2);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str1), "abc"));
        CHECK(0 == strcmp(str_cstr(p_str2), "def"));
        CHECK(0 == strcmp(str_cstr(p_str3), "abcdef"));
        mem_release(p_str1);
        mem_release(p_str2);
        mem_release(p_str3);
    }

    //-------------------------------------------------------------------------
    // Test str_insert function
    //-------------------------------------------------------------------------
    TEST(Verify_str_insert_should_insert_at_index_0)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_new("def");
        str_t* p_str3 = str_insert(p_str1, 0, p_str2);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str1), "abc"));
        CHECK(0 == strcmp(str_cstr(p_str2), "def"));
        CHECK(0 == strcmp(str_cstr(p_str3), "defabc"));
        mem_release(p_str1);
        mem_release(p_str2);
        mem_release(p_str3);
    }

    TEST(Verify_str_insert_should_insert_at_index_1)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_new("def");
        str_t* p_str3 = str_insert(p_str1, 1, p_str2);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str1), "abc"));
        CHECK(0 == strcmp(str_cstr(p_str2), "def"));
        CHECK(0 == strcmp(str_cstr(p_str3), "adefbc"));
        mem_release(p_str1);
        mem_release(p_str2);
        mem_release(p_str3);
    }

    TEST(Verify_str_insert_should_insert_at_index_2)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_new("def");
        str_t* p_str3 = str_insert(p_str1, 2, p_str2);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str1), "abc"));
        CHECK(0 == strcmp(str_cstr(p_str2), "def"));
        CHECK(0 == strcmp(str_cstr(p_str3), "abdefc"));
        mem_release(p_str1);
        mem_release(p_str2);
        mem_release(p_str3);
    }

    TEST(Verify_str_insert_should_insert_at_index_3)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_new("def");
        str_t* p_str3 = str_insert(p_str1, 3, p_str2);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str1), "abc"));
        CHECK(0 == strcmp(str_cstr(p_str2), "def"));
        CHECK(0 == strcmp(str_cstr(p_str3), "abcdef"));
        mem_release(p_str1);
        mem_release(p_str2);
        mem_release(p_str3);
    }

    TEST(Verify_str_insert_should_return_NULL_if_index_out_of_bound)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_new("def");
        CHECK(p_str1 != p_str2);
        CHECK(NULL == str_insert(p_str1, 4, p_str2));
        CHECK(0 == strcmp(str_cstr(p_str1), "abc"));
        CHECK(0 == strcmp(str_cstr(p_str2), "def"));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    //-------------------------------------------------------------------------
    // Test str_erase function
    //-------------------------------------------------------------------------
    TEST(Verify_str_erase_should_erase_first_char)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_erase(p_str1,0,1);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "bc"));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_erase_should_erase_second_char)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_erase(p_str1,1,2);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "ac"));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_erase_should_erase_last)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_erase(p_str1,2,3);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "ab"));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_erase_nothing_when_out_of_bounds)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_erase(p_str1,3,4);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "abc"));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_erase_nothing_when_range_is_of_length_0)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_erase(p_str1,1,1);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "abc"));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_erase_everything)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_erase(p_str1, 0, str_size(p_str1));
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), ""));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    //-------------------------------------------------------------------------
    // Test str_ function
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    // Test str_ function
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    // Test str_ function
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    // Test str_ function
    //-------------------------------------------------------------------------
}
