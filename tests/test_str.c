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
        CHECK(3 == str_size(p_str));
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
        CHECK(3 == str_size(p_str2));
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

    TEST(Verify_str_at_should_return_null_char_if_index_WAY_out_of_range)
    {
        str_t* p_str = str_new("abc");
        CHECK('\0' == str_at(p_str,42));
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
        CHECK(3 == str_size(p_str1));
        CHECK(0 == strcmp(str_cstr(p_str2),"abd"));
        CHECK(3 == str_size(p_str2));
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
        CHECK(0 == strcmp(str_cstr(p_str1), "abc"));
        CHECK(0 == strcmp(str_cstr(p_str2), "def"));
        CHECK(0 == strcmp(str_cstr(p_str3), "abcdef"));
        CHECK(6 == str_size(p_str3));
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
        CHECK(0 == strcmp(str_cstr(p_str1), "abc"));
        CHECK(0 == strcmp(str_cstr(p_str2), "def"));
        CHECK(0 == strcmp(str_cstr(p_str3), "defabc"));
        CHECK(6 == str_size(p_str3));
        mem_release(p_str1);
        mem_release(p_str2);
        mem_release(p_str3);
    }

    TEST(Verify_str_insert_should_insert_at_index_1)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_new("def");
        str_t* p_str3 = str_insert(p_str1, 1, p_str2);
        CHECK(0 == strcmp(str_cstr(p_str1), "abc"));
        CHECK(0 == strcmp(str_cstr(p_str2), "def"));
        CHECK(0 == strcmp(str_cstr(p_str3), "adefbc"));
        CHECK(6 == str_size(p_str3));
        mem_release(p_str1);
        mem_release(p_str2);
        mem_release(p_str3);
    }

    TEST(Verify_str_insert_should_insert_at_index_2)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_new("def");
        str_t* p_str3 = str_insert(p_str1, 2, p_str2);
        CHECK(0 == strcmp(str_cstr(p_str1), "abc"));
        CHECK(0 == strcmp(str_cstr(p_str2), "def"));
        CHECK(0 == strcmp(str_cstr(p_str3), "abdefc"));
        CHECK(6 == str_size(p_str3));
        mem_release(p_str1);
        mem_release(p_str2);
        mem_release(p_str3);
    }

    TEST(Verify_str_insert_should_insert_at_index_3)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_new("def");
        str_t* p_str3 = str_insert(p_str1, 3, p_str2);
        CHECK(0 == strcmp(str_cstr(p_str1), "abc"));
        CHECK(0 == strcmp(str_cstr(p_str2), "def"));
        CHECK(0 == strcmp(str_cstr(p_str3), "abcdef"));
        CHECK(6 == str_size(p_str3));
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
        CHECK(2 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_erase_should_erase_second_char)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_erase(p_str1,1,2);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "ac"));
        CHECK(2 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_erase_should_erase_last)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_erase(p_str1,2,3);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "ab"));
        CHECK(2 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_erase_nothing_when_out_of_bounds)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_erase(p_str1,3,4);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "abc"));
        CHECK(3 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_erase_nothing_when_range_is_of_length_0)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_erase(p_str1,1,1);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "abc"));
        CHECK(3 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_erase_everything)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_erase(p_str1, 0, str_size(p_str1));
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), ""));
        CHECK(0 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_erase_2_chars)
    {
        str_t* p_str1 = str_new("abcdef");
        str_t* p_str2 = str_erase(p_str1, 1, 3);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "adef"));
        CHECK(4 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_erase_3_chars)
    {
        str_t* p_str1 = str_new("abcdef");
        str_t* p_str2 = str_erase(p_str1, 1, 4);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "aef"));
        CHECK(3 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_erase_4_chars)
    {
        str_t* p_str1 = str_new("abcdef");
        str_t* p_str2 = str_erase(p_str1, 1, 5);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "af"));
        CHECK(2 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    //-------------------------------------------------------------------------
    // Test str_substr function
    //-------------------------------------------------------------------------
    TEST(Verify_str_substr_should_return_a_copy_of_the_string)
    {
        str_t* p_str1 = str_new("abcdef");
        str_t* p_str2 = str_substr(p_str1, 0, str_size(p_str1));
        CHECK(p_str1 != p_str2);
        CHECK(0 == str_compare(p_str1,p_str2));
        CHECK(6 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_substr_should_return_index_1_to_the_end)
    {
        str_t* p_str1 = str_new("abcdef");
        str_t* p_str2 = str_substr(p_str1, 1, str_size(p_str1));
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "bcdef"));
        CHECK(5 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_substr_should_return_index_0_to_one_before_the_end)
    {
        str_t* p_str1 = str_new("abcdef");
        str_t* p_str2 = str_substr(p_str1, 0, str_size(p_str1)-1);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "abcde"));
        CHECK(5 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_substr_should_return_index_1_to_3)
    {
        str_t* p_str1 = str_new("abcdef");
        str_t* p_str2 = str_substr(p_str1, 1, 4);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "bcd"));
        CHECK(3 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_substr_should_return_index_1_to_2)
    {
        str_t* p_str1 = str_new("abcdef");
        str_t* p_str2 = str_substr(p_str1, 1, 3);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "bc"));
        CHECK(2 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_substr_should_return_index_1_to_1)
    {
        str_t* p_str1 = str_new("abcdef");
        str_t* p_str2 = str_substr(p_str1, 1, 2);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), "b"));
        CHECK(1 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_substr_should_return_an_empty_string_for_a_range_of_0)
    {
        str_t* p_str1 = str_new("abcdef");
        str_t* p_str2 = str_substr(p_str1, 1, 1);
        CHECK(p_str1 != p_str2);
        CHECK(0 == strcmp(str_cstr(p_str2), ""));
        CHECK(0 == str_size(p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    //-------------------------------------------------------------------------
    // Test str_compare function
    //-------------------------------------------------------------------------
    TEST(Verify_str_compare_should_return_0_on_match)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_new("abc");
        CHECK(str_compare(p_str1, p_str2) == 0);
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_compare_should_return_less_than_zero_on_mismatch)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_new("abd");
        CHECK(str_compare(p_str1, p_str2) < 0);
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_compare_should_return_greater_than_zero_on_mismatch)
    {
        str_t* p_str1 = str_new("abd");
        str_t* p_str2 = str_new("abc");
        CHECK(str_compare(p_str1, p_str2) > 0);
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_compare_should_return_less_than_zero_if_case_is_different)
    {
        str_t* p_str1 = str_new("abC");
        str_t* p_str2 = str_new("abc");
        CHECK(str_compare(p_str1, p_str2) < 0);
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_compare_should_return_greater_than_zero_if_case_is_different)
    {
        str_t* p_str1 = str_new("abc");
        str_t* p_str2 = str_new("abC");
        CHECK(str_compare(p_str1, p_str2) > 0);
        mem_release(p_str1);
        mem_release(p_str2);
    }

    //-------------------------------------------------------------------------
    // Test str_find function
    //-------------------------------------------------------------------------
    TEST(Verify_str_find_should_find_a_string_at_index_0)
    {
        str_t* p_str1 = str_new("abcdcba");
        str_t* p_str2 = str_new("abc");
        CHECK(0 == str_find(p_str1, p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_find_should_find_a_string_at_index_1)
    {
        str_t* p_str1 = str_new("abcdcba");
        str_t* p_str2 = str_new("bcd");
        CHECK(1 == str_find(p_str1, p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_find_should_find_a_string_in_the_middle)
    {
        str_t* p_str1 = str_new("abcdcba");
        str_t* p_str2 = str_new("cdc");
        CHECK(2 == str_find(p_str1, p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_find_should_find_a_string_1_from_the_end)
    {
        str_t* p_str1 = str_new("abcdcba");
        str_t* p_str2 = str_new("dcb");
        CHECK(3 == str_find(p_str1, p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_find_should_find_a_string_at_the_end)
    {
        str_t* p_str1 = str_new("abcdcba");
        str_t* p_str2 = str_new("cba");
        CHECK(4 == str_find(p_str1, p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_find_should_find_first_occurrence)
    {
        str_t* p_str1 = str_new("_abcabc_");
        str_t* p_str2 = str_new("abc");
        CHECK(1 == str_find(p_str1, p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_find_should_not_find_any_occurrence)
    {
        str_t* p_str1 = str_new("_abcabc_");
        str_t* p_str2 = str_new("zzz");
        CHECK(SIZE_MAX == str_find(p_str1, p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    //-------------------------------------------------------------------------
    // Test str_rfind function
    //-------------------------------------------------------------------------
    TEST(Verify_str_rfind_should_find_a_string_at_index_0)
    {
        str_t* p_str1 = str_new("abcdcba");
        str_t* p_str2 = str_new("abc");
        CHECK(0 == str_rfind(p_str1, p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_rfind_should_find_a_string_at_index_1)
    {
        str_t* p_str1 = str_new("abcdcba");
        str_t* p_str2 = str_new("bcd");
        CHECK(1 == str_rfind(p_str1, p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_rfind_should_find_a_string_in_the_middle)
    {
        str_t* p_str1 = str_new("abcdcba");
        str_t* p_str2 = str_new("cdc");
        CHECK(2 == str_rfind(p_str1, p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_rfind_should_find_a_string_1_from_the_end)
    {
        str_t* p_str1 = str_new("abcdcba");
        str_t* p_str2 = str_new("dcb");
        CHECK(3 == str_rfind(p_str1, p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_rfind_should_find_a_string_at_the_end)
    {
        str_t* p_str1 = str_new("abcdcba");
        str_t* p_str2 = str_new("cba");
        CHECK(4 == str_rfind(p_str1, p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_rfind_should_find_last_occurrence)
    {
        str_t* p_str1 = str_new("_abcabc_");
        str_t* p_str2 = str_new("abc");
        CHECK(4 == str_rfind(p_str1, p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }

    TEST(Verify_str_rfind_should_not_find_any_occurrence)
    {
        str_t* p_str1 = str_new("_abcabc_");
        str_t* p_str2 = str_new("zzz");
        CHECK(SIZE_MAX == str_rfind(p_str1, p_str2));
        mem_release(p_str1);
        mem_release(p_str2);
    }
}
