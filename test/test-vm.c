#include "../src/kvm.h"
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(cond, message)                                                  \
    if (!(cond))                                                               \
    {                                                                          \
        fprintf(stderr, "[FAILED] '%s' at line %d\n", message, __LINE__);      \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        OK(message)                                                            \
    }

#define OK(message) fprintf(stdout, "[OK] %s\n", message);

void test_vm()
{
    {
        VM vm1;
        initVM(&vm1);
        for (int i = 0; i < 10; i++)
        {
            addConstant(&vm1, i * 10);
        }
        Instruction ins[2] = {
            /* LOAD 10 $1 */
            opAB(OP_LOAD, 1, 1),

            /* LOAD 20 $2 */
            opAB(OP_LOAD, 2, 2),

        };
        runVM(&vm1, ins, 2);
        // printRegister(&vm1, 1);
        ASSERT((vm1.regs[1] == 10), "opLoad");
    }
    {
        VM vm;
        initVM(&vm);
        for (int i = 0; i < 10; i++)
        {
            addConstant(&vm, i);
        }
        Instruction ins[3] = {
            /* LOAD 1 $5 */
            opAB(OP_LOAD, 1, 5),

            /* LOAD 20 $2 */
            opAB(OP_LOAD, 4, 2),

            /* ADD $5 $2 $3 */
            opABC(OP_MULT, 5, 2, 3),

        };
        runVM(&vm, ins, 3);
        ASSERT((vm.regs[3] == 4), "opMult");
    }
    // 
}

int main()
{
    test_vm();
    printf("\n\n----All tests passed----\n");
    return 0;
}