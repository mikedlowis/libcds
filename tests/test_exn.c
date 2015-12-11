
// Unit Test Framework Includes
#include "test.h"

// File To Test
#include "exn.h"

typedef struct {
    unsigned int branch0 : 1;
    unsigned int branch1 : 1;
    unsigned int branch2 : 1;
    unsigned int branch3 : 1;
    unsigned int branch4 : 1;
    unsigned int branch5 : 1;
    unsigned int branch6 : 1;
    unsigned int branch7 : 1;
} exn_test_state_t;

static int Exit_Status = 0;
void exit(int status) {
    Exit_Status = status;
    if (NULL != exn_handler())
        exn_handler()->state = EXN_DONE;
}

static void test_setup(void) {
    Exit_Status = 0;
}

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
TEST_SUITE(Exn) {
    //-------------------------------------------------------------------------
    // Test catch blocks
    //-------------------------------------------------------------------------
    TEST(Verify_a_catch_block_will_catch_a_matching_exception)
    {
        exn_test_state_t state = {0,0,0,0,0,0,0,0};
        try {
            state.branch0 = 1;
            throw(RuntimeException);
            state.branch1 = 1;
        } catch(RuntimeException) {
            state.branch2 = 1;
        }
        CHECK(state.branch0 == 1);
        CHECK(state.branch1 == 0);
        CHECK(state.branch2 == 1);
    }

    TEST(Verify_a_catch_block_will_catch_a_matching_exception_by_hierarchy)
    {
        exn_test_state_t state = {0,0,0,0,0,0,0,0};
        try {
            state.branch0 = 1;
            throw(AssertionException);
            state.branch1 = 1;
        } catch(RuntimeException) {
            state.branch2 = 1;
        }
        CHECK(state.branch0 == 1);
        CHECK(state.branch1 == 0);
        CHECK(state.branch2 == 1);
    }

    TEST(Verify_the_first_matching_catch_block_is_executed)
    {
        exn_test_state_t state = {0,0,0,0,0,0,0,0};
        try {
            state.branch0 = 1;
            throw(AssertionException);
            state.branch1 = 1;
        } catch(RuntimeException) {
            state.branch2 = 1;
        } catch(AssertionException) {
            state.branch3 = 1;
        }
        CHECK(state.branch0 == 1);
        CHECK(state.branch1 == 0);
        CHECK(state.branch2 == 1);
        CHECK(state.branch3 == 0);
    }

    TEST(Verify_non_matching_catch_blocks_are_ignored)
    {
        exn_test_state_t state = {0,0,0,0,0,0,0,0};
        try {
            state.branch0 = 1;
            throw(AssertionException);
            state.branch1 = 1;
        } catch(AbortException) {
            state.branch2 = 1;
        } catch(RuntimeException) {
            state.branch3 = 1;
        } catch(AssertionException) {
            state.branch4 = 1;
        }
        CHECK(state.branch0 == 1);
        CHECK(state.branch1 == 0);
        CHECK(state.branch2 == 0);
        CHECK(state.branch3 == 1);
        CHECK(state.branch4 == 0);
    }

    TEST(Verify_an_uncaught_exception_will_be_rethrown)
    {
        exn_test_state_t state = {0,0,0,0,0,0,0,0};
        try {
            state.branch0 = 1;
            try {
                state.branch1 = 1;
                throw(RuntimeException);
                state.branch2 = 1;
            } catch(AssertionException) {
                state.branch3 = 1;
            }
            state.branch4 = 1;
        } catch(RuntimeException) {
            state.branch5 = 1;
        }
        CHECK(state.branch0 == 1);
        CHECK(state.branch1 == 1);
        CHECK(state.branch2 == 0);
        CHECK(state.branch3 == 0);
        CHECK(state.branch4 == 0);
        CHECK(state.branch5 == 1);
    }

    //-------------------------------------------------------------------------
    // Test finally blocks
    //-------------------------------------------------------------------------
    TEST(Verify_a_finally_block_is_executed_after_an_uncaught_exception_is_thrown)
    {
        exn_test_state_t state = {0,0,0,0,0,0,0,0};
        try {
            state.branch0 = 1;
            try {
                throw(RuntimeException);
                state.branch1 = 1;
            } finally { state.branch2 = 1; }
        } catch(RuntimeException) {
            state.branch3 = 1;
        }
        CHECK(state.branch0 == 1);
        CHECK(state.branch1 == 0);
        CHECK(state.branch2 == 1);
        CHECK(state.branch3 == 1);
    }

    TEST(Verify_a_finally_block_is_executed_after_a_succesful_try_block)
    {
        exn_test_state_t state = {0,0,0,0,0,0,0,0};
        try {
            state.branch0 = 1;
        }
        catch(RuntimeException) { state.branch1 = 1; }
        finally { state.branch2 = 1; }
        CHECK(state.branch0 == 1);
        CHECK(state.branch1 == 0);
        CHECK(state.branch2 == 1);
    }

    //-------------------------------------------------------------------------
    // Test assertions
    //-------------------------------------------------------------------------
    TEST(Verify_successful_assertions_do_not_throw_an_exception)
    {
        exn_test_state_t state = {0,0,0,0,0,0,0,0};
        try {
            state.branch0 = 1;
            assert(true);
            state.branch1 = 1;
        }
        catch(AssertionException) { state.branch2 = 1; }
        CHECK(state.branch0 == 1);
        CHECK(state.branch1 == 1);
    }

    TEST(Verify_unsuccessful_assertions_throw_an_exception)
    {
        exn_test_state_t state = {0,0,0,0,0,0,0,0};
        try {
            assert(false);
            state.branch0 = 1;
        }
        catch(AssertionException) { state.branch1 = 1; }
        CHECK(state.branch0 == 0);
        CHECK(state.branch1 == 1);
    }

    //-------------------------------------------------------------------------
    // Test extraordinary conditions
    //-------------------------------------------------------------------------
    //TEST(Verify_an_uncaught_exception_terminates_the_program)
    //{
    //    throw(AssertionException);
    //    CHECK( Exit_Status == 1 );
    //}

    //TEST(Verify_an_invalid_exception_state_terminates_the_program)
    //{
    //    try {
    //        exn_handler()->state = EXN_DONE+1;
    //        exn_process();
    //    }
    //    CHECK( Exit_Status == 1 );
    //}
}
