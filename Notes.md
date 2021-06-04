# Notes for implementation of KVM

## Feature-set:
- Can handle strings, booleans, numbers, arrays and maps.
- Is a register based VM.


## Instruction set:

Example program:

```
LOAD 10 $0
LOAD 20 $1
ADD $0 $1 $2
```

## Constant Pool

> 4 June 2021

A constant is simply what the name implies.
It's a pool of constant values like numbers, strings, booleans etc. (For now we will only consider numbers).

Make the following changes to the VM:

1. A VM will have a pool of numbers (it can be an array)
2. On every instruction that previously took an inline value (A value that is embedded into the instruction itself) will now take an inline **index**.
3. Create a function `initVM` that intializes all registers to 0.
4. Add a test for `addConstant` function described below.

Previously, `LOAD 2 $0` meant "load the number 2 into register 0".

Now, `LOAD 2 $0` will mean, "load the constant value present at index 2 in the constant pool into register 0".

Say constant pool is : `[ 100, 120, 66, 123 ]`.

And the registers are: `[ 0 0 0 ... 0 ]`.

After, `LOAD 2 $0`, our registers will look like:
`[ 66 0 0 ... 0 ]`

Tips:
1. The constant pool can be a member variable of the VM struct.
2. Keep the array fixed in length for now.

You can imagine that the new VM's interface
will look like this:

```c
VM vm;
initVM(&vm);
int index = addConstant(&vm, 100);
// LOAD index $0
Instruction ins[1] = { opABC(OP_LOAD, index, 0) };
runVM(&vm, ins, 1);
```

The **addConstant** function takes a number, and it's to the VM's constant pool.
Then it returns the index in which it was added. The index can
be used by the user to refer to that number.