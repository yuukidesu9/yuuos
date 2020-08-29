global _start
[bits 32]
[extern kernel_main]
_start:
    ; Here we'll call our kernel function.
    call kernel_main
    ; And get into an infinite loop.
    jmp $