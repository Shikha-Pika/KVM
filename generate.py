import sys

# number of instructions converted so far
instr_count = 0

# convert a single KVM instruction to C code
def instr_to_c(code, operands):
  global instr_count
  c_opname = f'OP_{code}'
  c_operands = []
  
  for operand in operands:
    if operand[0] == '$':
      c_operands.append(int(operand[1:]))
    else:
      c_operands.append(int(operand))

  res = f'ins[{instr_count}].op = {c_opname};\n'
  for i in range(len(c_operands)):
    res += f'ins[{instr_count}].operands[i] = {c_operands[i]};\n'
  
  instr_count += 1
  return res

# convert an entire KVM source string to C code
def src_to_c(code):
  lines = code.split('\n')
  lines = list(filter(lambda line : len(line) >= 1, lines))
  code = 'Instruction ins[!@];\n\n'

  for line in lines:
    instr = line.split(' ')
    instr = list(filter(lambda s : len(s) >= 1, instr))
    code += f'/* {line} */\n'
    code += instr_to_c(instr[0], instr[1:]) + '\n'

  return code.replace('!@', str(instr_count))


def main():
  argv = sys.argv
  argc = len(argv)
  if argc != 2:
    print('Usage: op2c <source file>')
    return
  else:
    file = open(argv[1], 'r')
    src = file.read()
    out_file = open('out.c', 'w')
    out_file.write(src_to_c(src))

main()