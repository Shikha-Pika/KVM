# Notes for implementation of KVM

## Feature-set:
- Can handle Strings, Booleans, numbers, arrays and maps.
- Is a register based VM.
- Can serve as a programming language backend.


## Instruction set:

Detailed instruction set to be added later.

Example program:

```
LOAD 10 $0
LOAD 20 $1
ADD $0 $1 $2
```

## Constant Pool

> 4 June 2021

A constant is simply what the name implies.
It's a pool of constant values like numbers, strings, Booleans etc. (For now we will only consider numbers).

Make the following changes to the VM:

1. A VM will have a pool of numbers (it can be an array)
2. On every instruction that previously took an inline value (A value that is embedded into the instruction itself) will now take an inline **index**.
3. Create a function `initVM` that initializes all registers to 0.
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

## New value representation and Refactors
> 06 June 2021

### Suggested changes:
1. `addConstant` should return the index at which the constant was added.
    The user can keep this index and use it to refer to the value he stored later on.

2. The unit tests need some refactoring:
  - Currently, everything is tested in a single test block.
    So if the test fails, the terminal will simply log out `[FAILED] <message>`.
    Now, if you try to debug this you have *no idea* what exactly went wrong.
    Your best bet is to scourge through the entire code and scan every nook and cranny for a problem.

  - Now consider a scenario where you have multiple tests, each test-case tests a small part of the code.
    So a block testing `OP_LOAD` will only test the constant loading logic, a block testing `OP_ADD` will 
    test the loading logic + adding logic. Now, if the testcase for `OP_LOAD` fails, you know that there is
    something wrong with the constant loading logic, which narrows your search space down to 5-10 lines of code!

  - Following from the above, your task is to refactor the test cases into multiple blocks, each block
    must test one and only one feature of the VM. Example:

```cpp
void test_vm() 
{
  {
    VM vm;
    // use OP_LOAD
  }

  {
    VM vm;
    // use OP_ADD (and OP_LOAD too because OP_ADD can't be tested alone)
  }

  {
    VM vm1;
    VM vm2;
    // check if two VMs can run one after the other.
  }
}
```

### New value representation.
For this part, we won't actually *implement* the new value representation yet. 
But I'll try to have you come up with a way to represent them. In the mean time, we will basic string functionality.

Currently, our VM is only capable of using number values. But we want to use multiple kinds of
values. For now, let's keep it to `string`, `bool` and `double`. Later we will add 1-2 more types of 
values (Objects and integers).

Before we think about representing all values, let's represent strings first:

```cpp
typedef struct 
{
  const char* chars;
  int len;
} KString;

// constructor function for kStrings
KString* kstring_new(const char* chars, int len);
// destructor function for kStrings
void kstring_free(KString* kstr);
```

So that becomes your second task (after refactoring tests):
1. Implement the `KString` struct, and relevant constructor and destructor functions.
2. Once you have implemented it, add tests for `KString`. What kind of tests? Here is one example:

```cpp
{
  KString* kstr = kstring_new("hello", 5);
  ASSERT("kstr is not NULL, kstr->chars is "Hello" and  kstr->len is 5", "KString constructor");
}
```

Ok, now back to values.
One possible approach to represent multiple values as a single data type is:

```cpp
typedef struct
{
  bool boolVal;
  double fltVal;
  KString* strVal;
} Value;
```

But there is a problem with the above struct. 

- At any one point in time, a value can only be of a single type. Consider the following pseudo-code:

  ```js
  $0 = "abc" // $N = Nth register
  $1 = "xyz"
  
  $2 = $0 == $1 // $2 will now be false.
  
  $0 = 123
  $1 = 456
  ```

  Notice how at all times, each register is only storing a single type of value. (Note that once we've made this change, our registers will be `Value[]` instead of `int[]`).

  The point is : **Logically speaking, a value should not simultaneously store a number and a string at any one point in time.**  But in our current, model it can be done very easily by doing something like this:

  ```c
  Value v;
  v.boolVal = true;
  v.fltVal = 42.0f;
  ```

  If we're careful enough, we can perhaps make sure to only access the field which is needed. 

- When given a value, we don't know what type it is! Let's try to implement a function that prints a value to the terminal.

  ```c
  void valuePrint(Value const* v) {
      printf("%d", v.boolVal); // 1
      printf("%f", v.fltVal);  // 2
  }
  ```

  Which is correct? Line 1 or line 2? If the user called our function as demonstrated below, it leads to UB:

  ```c
  Value v;
  v.fltVal = 2.5;
  valuePrint(&v); // v.boolVal is garbage
  
  Value v2;
  v2.boolVal = false;
  valuePrint(v2); // v.fltVal is garbage
  ```

  

  ### Problem: What type is our value?

  Lets try to address the second problem first. 
  What can we do to store the datatype in a `Value`?
  What is the pragmatic way to do it in C?
  This is where you **stop** and think before moving on. The answer is right below this point.

  

  We can use an `enum` that stores the type tag.
  Before accessing a value's data fields, we check to see what type it is, and then access the corresponding data field.

  I want you to code this yourself, so I won't write the exact C code, but here is how the `valuePrint` function would look after this change:

  

  ```c
  void valuePrint(Value const* v) {
      if (v is of type double) {
          printf("%d", v->fltVal);
      } else if (v is of type string) {
          printf("%s", v->strVal);
      } else if (v is of type boolean) {
          printf("%s", v->boolVal ? "true" : "false");
      }
  }
  ```

  

  ### Problem: Is our value struct too big?

  Now let's come back to the first problem.  At any given point in time, **what is the largest number of bytes needed to store our value?**. 

   - `strVal` : 8 (*) bytes
   - `boolVal`: 4 bytes
   - `fltVal`: 8 bytes

  

  At any given point in time, we need at most 8 bytes to store the actual bits of our value, and 4 bytes to store the type tag. 
  So 12 in total (16 with padding).
  Since our value can only be of a single type at any given point in our program flow, we don't need to allocate entire 32 bytes, we can reuse the same 8 bytes for a string ptr, for a boolean and for a double.

  That's your final exercise: **Think of a way to shrink our value representation**.

  

  