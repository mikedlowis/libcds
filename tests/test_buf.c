// Unit Test Framework Includes
#include "test.h"

// File To Test
#include "buf.h"
#include "mem.h"

static void test_setup(void) { }

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
TEST_SUITE(Buffer) {
    //-------------------------------------------------------------------------
    // Test buf_new function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_new_returns_a_new_buffer_of_the_desired_size)
    {
        buf_t* buf = buf_new(5);
        CHECK( NULL != buf );
        CHECK( NULL != buf->buffer );
        CHECK( 5 == buf->size );
        CHECK( 0 == buf->reads );
        CHECK( 0 == buf->writes );
        mem_release(buf);
    }

    TEST(Verify_buf_new_returns_null_if_passed_a_size_of_0)
    {
        CHECK( NULL == buf_new(0) );
    }

    //-------------------------------------------------------------------------
    // Test buf_size function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_size_should_return_the_size_of_the_buffer)
    {
        buf_t* buf = buf_new(5);
        CHECK( 5 == buf_size( buf ) );
        mem_release(buf);
    }

    //-------------------------------------------------------------------------
    // Test buf_empty function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_empty_returns_1_when_buffer_is_empty)
    {
        buf_t buf = { NULL, 5, 1, 1 };
        CHECK( true == buf_empty( &buf ) );
    }

    TEST(Verify_buf_empty_returns_0_when_buffer_is_empty)
    {
        buf_t buf = { NULL, 5, 1, 2 };
        CHECK( false == buf_empty( &buf ) );
    }

    //-------------------------------------------------------------------------
    // Test buf_full function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_full_returns_1_if_buffer_is_full)
    {
        buf_t buf = { NULL, 5, 1, 6 };
        CHECK( true == buf_full( &buf ) );
    }

    TEST(Verify_buf_full_returns_0_if_buffer_empty)
    {
        buf_t buf = { NULL, 5, 1, 1 };
        CHECK( false == buf_full( &buf ) );
    }

    TEST(Verify_buf_full_returns_0_if_buffer_not_full)
    {
        buf_t buf = { NULL, 5, 1, 5 };
        CHECK( false == buf_full( &buf ) );
    }

    //-------------------------------------------------------------------------
    // Test buf_clear function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_clears_the_buffer_and_frees_the_contents)
    {
        buf_t* buf = buf_new(3);
        buf_write( buf, mem_box(0x1234) );
        buf_write( buf, mem_box(0x1235) );
        buf_write( buf, mem_box(0x1236) );
        buf_clear( buf );
        CHECK( buf->reads == 0 );
        CHECK( buf->writes == 0 );
        mem_release(buf);
    }

    //-------------------------------------------------------------------------
    // Test buf_read function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_read_should_return_NULL_if_buffer_is_empty)
    {
        buf_t* buf = buf_new(3);
        CHECK( NULL == buf_read( buf ) );
        mem_release(buf);
    }

    TEST(Verify_buf_read_should_return_the_next_piece_of_data_from_the_buffer)
    {
        buf_t* buf = buf_new(3);
        void* contents;
        buf_write( buf, mem_box(0x1234) );
        buf_write( buf, mem_box(0x1235) );
        buf_write( buf, mem_box(0x1236) );

        contents = buf_read(buf);
        CHECK( 0x1234 == mem_unbox(contents) );
        mem_release(contents);
        contents = buf_read(buf);
        CHECK( 0x1235 == mem_unbox(contents) );
        mem_release(contents);
        contents = buf_read(buf);
        CHECK( 0x1236 == mem_unbox(contents) );
        mem_release(contents);
        CHECK( NULL == buf_read(buf) );

        mem_release(buf);
    }

    //-------------------------------------------------------------------------
    // Test buf_write function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_write_should_return_0_if_buffer_is_full)
    {
        buf_t* buf = buf_new(1);
        void* box  = mem_box(0x1234);
        CHECK( true  == buf_write(buf, mem_box(0x1234)));
        CHECK( false == buf_write(buf, box));
        mem_release(box);
        mem_release(buf);
    }

    TEST(Verify_buf_write_should_return_1_if_data_successfully_wrote)
    {
        buf_t* buf = buf_new(1);
        CHECK( true == buf_write(buf, mem_box(0x1234)));
        mem_release(buf);
    }
}
