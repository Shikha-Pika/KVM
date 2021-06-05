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
    VM vm1, vm2;
    initVM(&vm1);
    initVM(&vm2);

    //for vm1
    for (int i = 0; i < 10; i++)
    {
        addConstant(&vm1, (i * 10));
    }

    //for vm2
    for (int i = 0; i < 10; i++)
    {
        addConstant(&vm2, (i + 2));
    }

    Instruction ins1[2] = {
        opAB(OP_LOAD, 2, 0),
        opAB(OP_LOAD, 4, 2),
    };

    Instruction ins2[3] = {
        opAB(OP_LOAD, 2, 1),
        opAB(OP_LOAD, 4, 3),
        opABC(OP_ADD, 1, 3, 2),
    };




    runVM(&vm1, ins2, 3);
    printRegister(&vm1, 1);
    ASSERT((vm1.regs[1] == 60), "Expected Output");
    printf("\n next \n"); //gap
    runVM(&vm2, ins1, 2);
    printRegister(&vm2, 1);
    ASSERT((vm2.regs[1] == 60), "Expected Output");

}

int main()
{
    test_vm();
    printf("\n\n----All tests passed----\n");
    return 0;
}