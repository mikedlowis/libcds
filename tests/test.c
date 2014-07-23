/**
  @file test.c
  @brief See header for details
  $Revision$
  $HeadURL$
  */
#include "test.h"

int Loop_Var;
char* Curr_Test;
test_results_t Test_Results = {0};

static const char* Results_String =
"\nUnit Test Summary"
"\n-----------------"
"\nTotal:  %d"
"\nPassed: %d"
"\nFailed: %d"
"\n\n"
;

int test_print_results(void) {
    (void)Loop_Var;
    (void)Curr_Test;
    printf(Results_String,
           Test_Results.total,
           Test_Results.total - Test_Results.failed,
           Test_Results.failed);
    return Test_Results.failed;
}

void test_fail(char* expr, char* file, int line) {
    Test_Results.failed++;
    printf("%s:%d:0:%s:FAIL\n\t%s\n", file, line, Curr_Test, expr); \
}

