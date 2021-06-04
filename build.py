import sys
import os

system = os.system

## change these variables to configure different compiler
## or add new source files.
cc = 'gcc'
src_dir = 'src'
bin_dir = 'bin'
test_dir = 'test'

exe_name = 'kvm'

def make_vm():
  system(f'{cc} src/kvm.c -c -o {bin_dir}/kvm.o')

def make_main():
  system(f'{cc} main.c {bin_dir}/kvm.o -o {bin_dir}/{exe_name}')

def make_all():
  make_vm()
  make_main()

def main():
  global bin_dir
  argc = len(sys.argv)
  argv = sys.argv
   
  os.makedirs(bin_dir, exist_ok=True)
  
  if argv != 2:
    make_all()
    return
  elif argv[1] == 'vm':
    make_vm()

main()