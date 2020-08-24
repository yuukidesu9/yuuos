; PurinPura-chan - 32-bit print
; --------------------------------
; She's the older sister of
; Purin-chan, and works in the
; protected mode.
; Code: Yuuki Sanada
; --------------------------------
[bits 32]
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

print_string_pm_loop:
    ; Pick a character...
    mov al, [ebx]
    mov ah, WHITE_ON_BLACK
    ; Checking the EOF...
    cmp al, 0
    je print_string_pm_done
    ; Increment loop, char and position...
    mov [edx], ax
    add ebx, 1
    add edx, 2
    jmp print_string_pm_loop

; And done!
print_string_pm_done:
    popa
    ret