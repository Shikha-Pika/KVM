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
    // TODO: 1. Add test for OP_LOAD and OP_ADD
    VM vm;
    initVM(&vm);
    for(int i = 0; i < 10; i++) {

        addConstant(&vm, (i*10));
    }
    Instruction ins[3] = {
        /* LOAD 10 $1 */
        opAB(OP_LOAD, 2, 1),
        /* LOAD 20 $2 */
        opAB(OP_LOAD, 4, 2),
        /* ADD $2 $2 $1 */
        opABC(OP_ADD, 2, 2, 1),
    };
    runVM(&vm, ins, 3);
    printRegister(&vm, 1);
    ASSERT((vm.regs[1] = 80), "Expected Output");
}

int main()
{
    test_vm();
    printf("\n\n----All tests passed----\n");
    return 0;
}