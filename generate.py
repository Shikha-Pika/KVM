import sys

# number of instructions converted so far
instr_count = 0

def make_op(opname, operands):
  opers = ', '.join(operands)
  if len(operands) == 3:
    return f'opABC({opname}, {opers})'
  elif len(operands) == 2:
    return f'opAB({opname}, {opers})'
  elif len(operands) == 1:
    return f'opA({opname}, {opers})'
  else:
    return f'op({opname})'

# convert a single KVM instruction to C code
def instr_to_c(code, operands):
  global instr_count
  c_opname = f'OP_{code}'
  c_operands = []
  
  for operand in operands:
    if operand[0] == '$':
      c_operands.append(operand[1:])
    else:
      c_operands.append(operand)
  

  res = f'{make_op(c_opname, c_operands)}, \n\n'
  
  instr_count += 1
  return res

# convert an entire KVM source string to C code
def src_to_c(code):
  lines = code.split('\n')
  lines = list(filter(lambda line : len(line) >= 1, lines))
  code = '{\nVM vm;\nInstruction ins[!@] = {\n'

  for line in lines:
    instr = line.split(' ')
    instr = list(filter(lambda s : len(s) >= 1, instr))
    code += f'\t/* {line} */\n'
    code += '\t' + instr_to_c(instr[0], instr[1:])  

  return (code.replace('!@', str(instr_count))  
    + '};\nrunVM(&vm, ins, ' 
    + str(instr_count) 
    + ');\n}')


def main():
  argv = sys.argv
  argc = len(argv)
  if argc != 2:
    print('Usage: op2c <source file>')
    return
  else:
    file = open(argv[1], 'r')
    src = file.read()
    out_file = open('scratch/out.c', 'w')
    out_file.write(src_to_c(src))

main()