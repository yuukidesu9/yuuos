extern interrupt_handler

; Handle the interrupts that don't return error codes,
; such as 0h to 7h, 9h, 15h and 16h.
%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    push dword 0
    push dword %1
    jmp common_interrupt_handler
%endmacro

; Handle the interrupts that return error codes,
; such as 8h, 10h, 13h and 14h.
%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    push dword %1
    jmp common_interrupt_handler
%endmacro

; Handle our interrupts.
common_interrupt_handler:
	; Save the registers.
	push eax ; General-purpose register A
	push ebx ; General-purpose register B
	push ecx ; General-purpose register C
	push edx ; General-purpose register D
	push ebp ; Bottom stack pointer
	push esi ; Stack index
	push edi ; Data index

    ; Call the C function to handle
    ; the interrupt.
    call interrupt_handler

    ; Restore the registers after calling
    ; the interrupt, in a stacked manner.
	pop	edi ; Data index
	pop	esi ; Stack index
	pop	ebp ; Bottom stack pointer
	pop	edx ; General-purpose register D
	pop	ecx ; General-purpose register C
	pop	ebx ; General-purpose register B
    pop eax ; General-purpose register A

	; Restore and add stack pointer.
	add esp, 8

	; Return to code that was being executed before.
	iret

; Int 1 - Keyboard interrupt, no error code
no_error_code_interrupt_handler	33

; Int 2 - Paging interrupt, no error code
;no_error_code_interrupt_handler 14