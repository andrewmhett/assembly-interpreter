# assembly-interpreter

This is a simple assembly language interpreter. It makes use of 26 named registers (a-z) and up to 50 labels in a single program. It also has the ability to print messages to stdout.

## Instruction Set
```
Instruction  Operands                                        Description
MOV          [(<int> or <register>) <register>]              Moves a value to a register.
ADD          [(<int> or <register>) <register>]              Adds a value to a register.
SUB          [(<int> or <register>) <register>]              Subtracts a value from a register.
MUL          [(<int> or <register>) <register>]              Multiplies the value in a register by another value.
DIV          [(<int> or <register>) <register>]              Divides the value in a register by another value.
CMP          [(<int> or <register>) (<int or <register>)]    Saves the difference between two operands for later use by conditional jumps.
JMP          [<label>]                                       Jumps the interpreter to a specific label.
JLT          [<label>]                                       Jumps the interpreter to a specific label if the difference stored by CMP is less than zero.
JGT          [<label>]                                       Jumps the interpreter to a specific label if the difference stored by CMP is greater than zero.
JET          [<label>]                                       Jumps the interpreter to a specific label if the difference stored by CMP is equal to zero.
JRO          [(<int> or <register>)]                         Jumps the interpreter with a specified relative offest
MSG          [(<int> or <register> or <string>) ...]         Formats and prints a message to stdout with any number of operands
```
