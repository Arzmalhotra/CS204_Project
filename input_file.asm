# RISC-V Assembly Code to Test Assembler

# Initialize registers
addi x1, x0, 10       # Load immediate value 10 into x1
addi x2, x0, 20       # Load immediate value 20 into x2

# R Format Instructions
add x3, x1, x2        # Add x1 and x2, store result in x3
sub x4, x2, x1        # Subtract x1 from x2, store result in x4
and x5, x1, x2        # Bitwise AND of x1 and x2
or  x6, x1, x2        # Bitwise OR of x1 and x2
xor x7, x1, x2        # Bitwise XOR of x1 and x2
sll x8, x1, x0        # Shift left logical (x1 by 0 bits)
srl x9, x2, x0        # Shift right logical (x2 by 0 bits)
slt x10, x1, x2       # Set less than (x1 < x2 ? 1 : 0)
sra x11, x2, x0       # Shift right arithmetic (x2 by 0 bits)
mul x12, x1, x2       # Multiply (x1 * x2)
div x13, x2, x1       # Divide (x2 / x1)
rem x14, x2, x1       # Remainder (x2 % x1)

# I Format Instructions
addi x15, x0, -5      # Load immediate value -5 into x15
andi x16, x15, 3      # Bitwise AND with immediate value, store in x16
ori  x17, x15, 7      # Bitwise OR with immediate value, store in x17
lb   x18, 0(x15)      # Load byte from memory address in x15 into x18
lh   x19, 4(x15)      # Load halfword from memory address in x15 into x19
lw   x20, 8(x15)      # Load word from memory address in x15 into x20
ld   x21, 16(x15)     # Load doubleword from memory address in x15 into x21
jalr x22, 0(x15)      # Jump and link: jump to address (x15 + 0) and store return address in x22

# S Format Instructions
sb   x18, 0(x20)      # Store byte: store the least significant byte of x18 at memory address in x20
