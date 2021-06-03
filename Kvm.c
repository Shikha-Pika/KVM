#include "kvm.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

Instruction opABC(Opcode op, int a, int b, int c)
{
    Instruction inst;
    inst.rA = a;
    inst.rB = b;
    inst.rC = c;
    inst.op = op;
    return inst;
}

Instruction opAB(Opcode op, int a, int b)
{
    Instruction inst;
    inst.rA = a;
    inst.rB = b;
    inst.op = op;
    return inst;
}

// printRegister(VM* vm, int i) -> prints the ith register of the VM [vm]
void printRegister(VM *vm, int i)
{
    printf("R_R%d - [ %d ]\n", i, vm->regs[i]);
}

// runVM(VM* vm, Instruction* ins, int n_ins) -> executes the instructions present in
//      the buffer [ins]
void runVM(VM *vm, Instruction *ins, int numInstrs)
{
    for (int i = 0; i < numInstrs; i++)
    {
        const Instruction instr = ins[i];
        switch (instr.op)
        {
        case OP_LOAD:
        {
            const int r_no = instr.rB;
            const int value = instr.rA;
            vm->regs[r_no] = value;
            break;
        }
        case OP_ADD:
        {
            const int r_no = instr.rC;
            const int value1 = instr.rA;
            const int value2 = instr.rB;
            vm->regs[r_no] = vm->regs[value1] + vm->regs[value2];
            break;
        }
        default:
            fprintf(stderr, "Invalid Opcode!");
            exit(1);
            break;
        }
    }
}
