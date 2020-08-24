[bits 32]
[extern main]
; Here we'll call our kernel function.
call main
; And get into an infinite loop.
jmp $