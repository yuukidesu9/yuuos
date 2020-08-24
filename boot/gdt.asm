; Kijutsu-chan - GDT descriptor
; --------------------------------
; She's our GDT descriptor, and
; will pass stuff to the 32-bit
; mode waifus.
; Code: Yuuki Sanada
; --------------------------------
; It always starts with a null byte.
gdt_start:
    dd 0x0
    dd 0x0

; Then... our code segment.
gdt_code:
    ; Length (16-bit):
    dw 0xffff
    ; Segment base (first 16 bits):
    dw 0x0
    ; Segment base (more 8 bits):
    db 0x0
    ; Flags (first 8 bits):
    db 10011010b
    ; Flags (more 4 bits)
    ; and Segment length (last 4 bits):
    db 11001111b
    ; Segment base (last 8 bits)
    db 0x0

; Data segment.
; Same parameters.
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

; Here's our descriptor:
gdt_descriptor:
    ; Size minus 1.
    dw gdt_end - gdt_start - 1
    ; Start address.
    dd gdt_start

; Constants - We'll use them later!
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
