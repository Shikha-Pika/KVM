#ifndef KVM_H
#define KVM_H
#define NUM_REGS 10
#define MAX_CONSTANTS 100
#include <stddef.h>

typedef enum
{
    OP_LOAD,
    OP_ADD,
    OP_MULT,
    OP_SUB,
    OP_DIV
} Opcode;

typedef struct
{
    Opcode op;
    size_t rA, rB, rC;
} Instruction;

typedef struct
{
    int regs[NUM_REGS];
    size_t constPool[MAX_CONSTANTS];
    int numCount;
} VM;

// function prototypes

Instruction opAB(Opcode op, int a, int b);
Instruction opABC(Opcode op, int a, int b, int c);
void initVM(VM *vm);
void addConstant(VM *vm, int num);
void printRegister(VM *vm, int i);
void runVM(VM *vm, Instruction *ins, int numInstrs);

#endif