#include "../src/kvm.h"
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(cond, message)                                                  \
    if (!(cond))                                                               \
    {                                                                          \
        fprintf(stderr, "[Failed] '%s' at line %d\n", message, __LINE__);      \
        exit(1);                                                               \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        OK(message)                                                            \
    }

#define OK(message) fprintf(stdout, "[OK] %s", message);

void test_vm()
{
    /// TODO: 1. Add test for OP_LOAD and OP_ADD
}

int main()
{
    test_vm();
    printf("\n\n----All tests passed----\n");
    return 0;
}