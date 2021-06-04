{
    VM vm;
    Instruction ins[4] = {
        /* LOAD 10 $1 */
        opAB(OP_LOAD, 10, 1),

        /* LOAD 20 $2 */
        opAB(OP_LOAD, 20, 2),

        /* ADD $1 $2 $3 */
        opABC(OP_ADD, 1, 2, 3),

        /* ADD $3 $3 $0 */
        opABC(OP_ADD, 3, 3, 0),
    };
    runVM(&vm, ins, 4);
}