Instruction ins[3];

/* LOAD 10 $1 */
ins[0].op = OP_LOAD;
ins[0].operands[i] = 10;
ins[0].operands[i] = 1;

/* LOAD 20 $2 */
ins[1].op = OP_LOAD;
ins[1].operands[i] = 20;
ins[1].operands[i] = 2;

/* ADD $1 $2 $3 */
ins[2].op = OP_ADD;
ins[2].operands[i] = 1;
ins[2].operands[i] = 2;
ins[2].operands[i] = 3;

