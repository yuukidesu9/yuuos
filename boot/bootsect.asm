[org 0x7c00]
KERNEL_OFFSET equ 0x1000 ; The same one we used when linking the kernel
    
    mov [BOOT_DRIVE], dl ; Set the boot drive (= this one)
    mov bp, 0x9000
    mov sp, bp
    ; Let's greet the user!
    mov bx, GREET
    call print
    call print_nl
    
    mov bx, MSG_REAL_MODE 
    call print
    call print_nl

    call load_kernel ; LOAD ZE KERNEL
    call switch_to_pm ; Let's switch to our protected mode!
    jmp $ ; Never executed

%include "boot/boot_print.asm"
%include "boot/boot_disk.asm"
%include "boot/32bit-gdt.asm"
%include "boot/32bit-print.asm"
%include "boot/32bit-switch.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call print_nl

    mov bx, KERNEL_OFFSET ; Read from disk and store in 0x1000
    mov dh, 16
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm
    call KERNEL_OFFSET ; Give control to the kernel
    jmp $ ; Stay here when the kernel returns control to us (if ever)


BOOT_DRIVE db 0 ; It is a good idea to store it in memory because 'dl' may get overwritten
MSG_REAL_MODE db "Entered 16-bit Real Mode.", 0
MSG_PROT_MODE db "Entered 32-bit Protected Mode.", 0
; Note: this and other texts in 32-bit mode will be printed from the start of the
; screen, aka position 0, 0.
MSG_LOAD_KERNEL db "Loading kernel into memory...", 0
GREET db "Hello, world!", 0

; padding
times 510 - ($-$$) db 0
dw 0xaa55