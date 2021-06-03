#include "kvm.h"

int main()
{
    VM vm;
    Instruction ins[3];
    vm.regs[0] = 0;
    vm.regs[1] = 0;
    vm.regs[2] = 0;

    ins[0] = opAB(OP_LOAD, 10, 0);
    ins[1] = opAB(OP_LOAD, 20, 1);
    ins[2] = opABC(OP_ADD, 0, 1, 2);

    runVM(&vm, ins, 3);
    printRegister(&vm, 0); // 10
    printRegister(&vm, 1); // 20
    printRegister(&vm, 2); //30
}
