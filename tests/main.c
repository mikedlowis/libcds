#include "test.h"

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    RUN_TEST_SUITE(Vector);
    RUN_TEST_SUITE(List);
    RUN_TEST_SUITE(Buffer);
    RUN_TEST_SUITE(String);
    RUN_TEST_SUITE(RBT);
    RUN_TEST_SUITE(Exn);
    RUN_TEST_SUITE(Mem);
    RUN_TEST_SUITE(Set);
    return PRINT_TEST_RESULTS();
}
