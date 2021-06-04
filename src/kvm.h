#ifndef KVM_H
#define KVM_H
#define NUM_REGS 10 

typedef enum
{
    OP_LOAD,
    OP_ADD
} Opcode;

typedef struct
{
    Opcode op;
    int rA, rB, rC;
} Instruction;

typedef struct
{
    int regs[NUM_REGS];
} VM;

//function prototypes

Instruction opAB(Opcode op, int a, int b);
Instruction opABC(Opcode op, int a, int b, int c);
void printRegister(VM *vm, int i);
void runVM(VM *vm, Instruction *ins, int numInstrs);

#endif