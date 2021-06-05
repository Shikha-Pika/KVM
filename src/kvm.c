#include "kvm.h"
#include <stdbool.h>
#include <stdio.h>
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

// initializing the register values
void initVM(VM *vm)
{
    for (int i = 0; i < 100; i++)
    {
        vm->regs[i] = 0;
    }
    vm->numCount = 0;
}

void addConstant(VM *vm, int num)
{
    if (vm->numCount < MAX_CONSTANTS)
    {
        vm->constPool[vm->numCount++] = num;
    }
}

void printRegister(VM *vm, int i)
{
    printf("R_R%d - [ %d ]\n", i, vm->regs[i]);
}

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
            const int poolIndex = instr.rA;
            const int value = vm->constPool[poolIndex];
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
