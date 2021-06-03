#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define NUM_REGS 3

typedef enum
{
    OP_LOAD,
    OP_ADD
} Opcode;

typedef struct
{
    Opcode op;
    int operands[3];
} Instruction;

typedef struct
{
    int regs[NUM_REGS];
} VM;

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
            const int r_no = instr.operands[1];
            const int value = instr.operands[0];
            vm->regs[r_no] = value;
            break;
        }
        case OP_ADD:
        {
            const int r_no = instr.operands[2];
            const int value1 = instr.operands[0];
            const int value2 = instr.operands[1];
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

int main()
{
    VM vm;
    Instruction ins[3];
    vm.regs[0] = 0;
    vm.regs[1] = 0;
    vm.regs[2] = 0;

    ins[0].op = OP_LOAD;
    ins[0].operands[0] = 10;
    ins[0].operands[1] = 0;

    ins[1].op = OP_LOAD;
    ins[1].operands[0] = 20;
    ins[1].operands[1] = 1;

    ins[2].op = OP_ADD;
    ins[2].operands[0] = 0;
    ins[2].operands[1] = 1;
    ins[2].operands[2] = 2;

    runVM(&vm, ins, 3);
    printRegister(&vm, 0); // 10
    printRegister(&vm, 1); // 20
    printRegister(&vm, 2); //30
}
