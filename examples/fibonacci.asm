; this is an example of another conditional
; loop which computes N number of elements
; in the fibonacci sequence

msg "F0: " 0
mov 1 b
fib:
add 1 d
mov b a
mov c b
mov 0 c
add a c
add b c
msg "F" d ": " c
cmp d 10
jlt fib
