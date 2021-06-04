#include "src/kvm.h"

int main()
{
    VM vm;
    vm.regs[0] = 0;
    vm.regs[1] = 0;
    vm.regs[2] = 0;

    Instruction ins[3] = {
    	/* LOAD 10 $1 */
	    opAB(OP_LOAD, 10, 1), 
	    /* LOAD 20 $2 */
	    opAB(OP_LOAD, 20, 2), 
    	/* ADD $2 $2 $1 */
	    opABC(OP_ADD, 2, 2, 1), 

    }; 

    runVM(&vm, ins, 3);
    printRegister(&vm, 0); // 10
    printRegister(&vm, 1); // 20
    printRegister(&vm, 2); //30
}
