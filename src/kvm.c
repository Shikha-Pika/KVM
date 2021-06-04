#include "kvm.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
int numCount = 0;

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
}

// addConstant(VM *vm, int num) -> adds constants into the pool
void addConstant(VM *vm, int num) { vm->constPool[numCount++] = num; }

// printRegister(VM* vm, int i) -> prints the ith register of the VM [vm]
void printRegister(VM *vm, int i)
{
    printf("R_R%d - [ %d ]\n", i, vm->regs[i]);
}

// poolVal(VM *vm, int index) -> extracts the constant from the pool
int poolVal(VM *vm, int index) { return vm->constPool[index]; }

// runVM(VM* vm, Instruction* ins, int n_ins) -> executes the instructions
// present in
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
            const int poolIndex = instr.rA;
            const int value = poolVal(vm, poolIndex);
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
