Instruction ins[3] = {
	/* LOAD 10 $1 */
	opAB(OP_LOAD, 10, 1), 

	/* LOAD 20 $2 */
	opAB(OP_LOAD, 20, 2), 

	/* ADD $2 $2 $1 */
	opABC(OP_ADD, 2, 2, 1), 

};