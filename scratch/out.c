{
VM vm;
Instruction ins[3] = {
	/* LOAD 1 $5 */
	opAB(OP_LOAD, 1, 5), 

	/* LOAD 20 $2 */
	opAB(OP_LOAD, 20, 2), 

	/* ADD $5 $2 $3 */
	opABC(OP_ADD, 5, 2, 3), 

};
runVM(&vm, ins, 3);
}