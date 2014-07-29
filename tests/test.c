/**
  @file test.c
  @brief See header for details
  $Revision$
  $HeadURL$
  */
#include "test.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

jmp_buf Landing_Pad;
int Loop_Var;
char* Curr_Test;
test_results_t Test_Results = {0,0,0};

static const char* Results_String =
"\nUnit Test Summary"
"\n-----------------"
"\nTotal:  %d"
"\nPassed: %d"
"\nFailed: %d"
"\n\n"
;

static void handle_signal(int sig) {
    puts("Handle Signal");
    switch(sig) {
        case SIGABRT:
        case SIGBUS:
        case SIGFPE:
        case SIGILL:
        case SIGSEGV:
        case SIGSYS:
            fprintf(stderr,"%s:%d:0:%s:CRASH (signal: %d)\n\t\n", __FILE__, __LINE__, Curr_Test, sig); \
            exit(1);
            //longjmp(Landing_Pad,1);
            break;

        default:
            fprintf(stderr,"CRASH (signal %d): %s\n", sig, Curr_Test);
            break;
    }
}

int test_start(void) {
    int rval = setjmp(Landing_Pad);
    if(0 == rval) {
        signal(SIGABRT, handle_signal);
        signal(SIGBUS,  handle_signal);
        signal(SIGFPE,  handle_signal);
        signal(SIGILL,  handle_signal);
        signal(SIGSEGV, handle_signal);
        signal(SIGSYS,  handle_signal);
    }
    return rval;
}

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

