
// Unit Test Framework Includes
#include "test.h"

// File To Test
#include "exn.h"

static void test_setup(void) { }

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
TEST_SUITE(Exn) {
    //-------------------------------------------------------------------------
    // Test catch blocks
    //-------------------------------------------------------------------------
    TEST(Verify_a_catch_block_will_catch_a_matching_exception)
    {
        int counter = 0;
        try { throw(RuntimeException); }
        catch(RuntimeException) { counter++; }
        CHECK(counter == 1);
    }

    TEST(Verify_a_catch_block_will_catch_a_matching_exception_by_hierarchy)
    {
        int counter = 0;
        try { throw(AssertionException); }
        catch(RuntimeException) { counter++; }
        CHECK(counter == 1);
    }

    TEST(Verify_the_first_matching_catch_block_is_executed)
    {
        int counter = 0;
        try { throw(AssertionException); }
        catch(RuntimeException) { counter++; }
        catch(AssertionException) { counter++; }
        CHECK(counter == 1);
    }

    TEST(Verify_non_matching_catch_blocks_are_ignored)
    {
        int counter = 0;
        try { throw(AssertionException); }
        catch(AbortException) { counter++; }
        catch(RuntimeException) { counter++; }
        catch(AssertionException) { counter++; }
        CHECK(counter == 1);
    }

    TEST(Verify_an_uncaught_exception_will_be_rethrown)
    {
        int counter = 0;
        try {
            counter++;
            try { throw(RuntimeException); }
            catch(AssertionException) { counter++; }
            counter++;
        } catch(RuntimeException) {
            counter++;
        }
        CHECK(counter == 2);
    }

    //-------------------------------------------------------------------------
    // Test finally blocks
    //-------------------------------------------------------------------------
    TEST(Verify_a_finally_block_is_executed_after_an_uncaught_exception_is_thrown)
    {
        int counter = 0;
        try {
            counter++;
            try { throw(RuntimeException); }
            finally { counter++; }
        } catch(RuntimeException) {
            counter++;
        }
        CHECK(counter == 3);
    }

    TEST(Verify_a_finally_block_is_executed_after_a_succesful_try_block)
    {
        int counter = 0;
        try {
            counter++;
        }
        catch(RuntimeException) { counter++; }
        finally { counter++; }
        CHECK(counter == 2);
    }

    //-------------------------------------------------------------------------
    // Test assertions
    //-------------------------------------------------------------------------
    TEST(Verify_successful_assertions_do_not_throw_an_exception)
    {
        int counter = 0;
        try {
            assert(true);
            counter++;
        }
        catch(AssertionException) { counter--; }
        CHECK(counter == 1);
    }

    TEST(Verify_successful_assertions_do_not_throw_an_exception)
    {
        int counter = 0;
        try {
            assert(false);
            counter++;
        }
        catch(AssertionException) { counter--; }
        CHECK(counter == -1);
    }
}
