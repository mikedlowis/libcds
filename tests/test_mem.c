// Unit Test Framework Includes
#include "test.h"

// File To Test
#include "mem.h"

static void test_setup(void) { }

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
TEST_SUITE(Mem) {
    TEST(Verify_mem_can_summarize_leaks)
    {
        void* p_obj = mem_allocate(sizeof(4),NULL);
        extern void summarize_leaks(void);
        summarize_leaks();
        mem_release( p_obj );
    }
}
