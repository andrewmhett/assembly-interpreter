; this is an example of a conditional loop
; this program will continue adding values to registers
; a, b, and c until register a reaches 10.

top:
msg "--------"
add 1 a
add 2 b
add 3 c
msg "reg a: " a
msg "reg b: " b
msg "reg c: " c
cmp a 5
jgt a_greater_than_five
cmp a 10
jlt top
jet bottom
a_greater_than_five:
msg "reg a is greater than 5"
cmp a 10
jlt top
bottom:
msg "Finished looping."
