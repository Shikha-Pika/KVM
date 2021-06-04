OUT_DIR=bin
EXE=$OUT_DIR/kvm

if [[ $1 == "all" ]]
then 
  gcc src/kvm.c -c -o $OUT_DIR/kvm.o
  gcc main.c $OUT_DIR/kvm.o -o $EXE;
elif [[ $1 == "vm" ]]
then 
  gcc src/kvm.c -o $OUT_DIR/kvm.o
else 
  gcc main.c $OUT_DIR/kvm.o -o $EXE
fi