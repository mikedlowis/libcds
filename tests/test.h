/**
  @file test.h
  @brief TODO: Describe this file
  $Revision$
  $HeadURL$
  */
#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <setjmp.h>

#define CHECK(expr) \
    if (!(expr)) { \
        test_fail(#expr,__FILE__,__LINE__-1); \
        break; \
    }

#define TEST(desc)        \
    Curr_Test = #desc;    \
    Test_Results.total++; \
    test_setup();         \
    if(0 == test_start()) \
        for(Loop_Var = 0; Loop_Var < 1; Loop_Var++)

#define TEST_SUITE(name) void name(void)

#define RUN_TEST_SUITE(name) \
    extern TEST_SUITE(name); \
    name();

#define PRINT_TEST_RESULTS test_print_results

typedef struct {
    unsigned int total;
    unsigned int passed;
    unsigned int failed;
} test_results_t;

extern jmp_buf Landing_Pad;
extern int Loop_Var;
extern char* Curr_Test;
extern test_results_t Test_Results;

int test_start(void);
int test_print_results(void);
void test_fail(char* expr, char* file, int line);

#endif /* TEST_H */
