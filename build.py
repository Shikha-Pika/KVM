import sys
from os import system

## change these variables to configure different compiler
## or add new source files.
cc = 'gcc'
src_dir = 'src/'
bin_dir = 'bin/'
test_dir = 'test/'

exe_name = 'kvm'

def make_vm():
  system(f'{cc} src/kvm.c -c -o {bin_dir}/kvm.o')

def make_main():
  system(f'{cc} main.c {bin_dir}/kvm.o -o {bin_dir}/{exe_name}')

def make_all():
  make_vm()
  make_main()

def main():
  argc = len(sys.argv)
  argv = sys.argv
  system('mkdir -p {bin_dir}')
  if argv != 2:
    make_all()
    return
  elif argv[1] == 'vm':
    make_vm()

main()