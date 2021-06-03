if [[ $1 == "all" ]]
then 
  gcc kvm.c -c -o kvm.o
  gcc main.c kvm.o;
elif [[ $1 == "vm" ]]
then 
  gcc kvm.c -o kvm.o
else 
  gcc main.c kvm.o
fi