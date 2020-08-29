[org 0x7C00]
; Dokusha-chan - Boot sector
; --------------------------------
; A simple cute boot sector for
; the YuuOS floppy microkernel.
; Code: Yuuki Sanada
; --------------------------------
; Here's our kernel offset.
KERNEL_OFFSET equ 0x1000
    ; Welp, time to load from the drive!
    mov [BOOT_DRIVE], dl
    ; Let's put the stack far from us,
    ; right?
    mov bp, 0x9000
    mov sp, bp
    ; Inform the user!
    mov bx, REALMODE
    call print
    call print_nl
    ; Now, sing with me!
    ; The itsy bitsy kernel
    ; was loaded into memory,
    call load_kernel
    ; Then came protected mode
    ; to show it into the screen
    call switch_protmode
    ; As if an infinite loop would run.
    ; Pssh.
    jmp $

; We'll append the disk reading
; part of our code.
%include "boot\print.asm"
%include "boot\32bit-switch.asm"
%include "boot\gdt.asm"
%include "boot\32bit-print.asm"
; Time to pop those stuff open!
disk_load:
    pusha
    push dx
    ; The AH register stores the function
    ; used in interrupt 0x13.
    ; In this case, 002 means 'read'.
    mov ah, 0x02
    ; The AL register stores the number
    ; of sectors to read (0x01 to 0x80).
    ; In this case, it's using DH's value,
    ; which is 2 (0x02) sectors.
    mov al, dh
    ; The CL register stores where we
    ; can start reading the disk.
    ; In this case, the second (0x02)
    ; sector.
    mov cl, 0x02
    ; The CH register stores the number
    ; of the cylinder (0x00 to 0x3FF).
    ; In this case, it's the first one,
    ; so it's 0 (0x00).
    mov ch, 0x00
    ; The DH register stores which head
    ; we will use (0x00 to 0x0F).
    ; In our case, it's the first one
    ; (0x00).
    mov dh, 0x00
    ; Call the interrupt and read!
    int 0x13
    ; In case of error...
    jc disk_error
    ; ...but if there's no errors...
    pop dx
    ; Compare the number of sectors read.
    cmp al, dh
    ; And in case of errors...
    jne sectors_error
    ; ...if no errors...
    popa
    ; ...we stop.
    ret

disk_error:
    ; We print an error message...
    mov bx, DISK_ERR
    call print
    call print_nl
    ; We pick the error code...
    mov dh, ah
    ; Print our error code...
    call print_hex
    ; ...and go into full infinite loop mode!
    jmp disk_load
    ; jmp disk_loop
    
sectors_error:
    ; We print an error message.
    mov bx, SECTORS_ERR
    call print
    
; Infinite loop time!
disk_loop:
    jmp $

DISK_ERR db "ERROR: disk read error", 0
RETRY db "Retrying...", 0
SECTORS_ERR db "ERROR: incorrect number of read sectors", 0
; Now for the important functions:
; First, the kernel loader.
; It'll get into 16-bit (real) mode.
[bits 16]
load_kernel:
    ; Let's tell the user,
    ; shall we?
    mov bx, KRNLLOAD
    call print
    call print_nl
    
    ; Time to read our kernel from disk.
    mov bx, KERNEL_OFFSET
    mov dh, 0x02
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret
; Sing with me!
; Dev'ers...
; Push your... floppy... disk up...to the... moon! 
; Bro, whatcha tryna do?
; 32 bits of magic in the air~
[bits 32]
; Head to toe, so playa!
begin_pm:
    ; A-look out-uh!
    ; *synth hits*
    ; Pop up, it's string time (string time)
    ; String time (string time)
    mov ebx, PROTMODE
    ; Guess who's on again!
    call print_string_pm
    ; You'd better run (that stuff),
    ; you'd better run (that stuff)
    call KERNEL_OFFSET
    ; Or else this is gonna be workin'
    ; (show up)
    jmp $
; Here we'll store some text.
; How about a 'Hello!'?
; P.S.: Strings have to finish
; with a null byte, that's why
; the zero is after the string
; without quotes.
BOOT_DRIVE db 0
REALMODE db "Entered 16-bit real mode.", 0
KRNLLOAD db "Loading kernel into memory.", 0
PROTMODE db "Entered 32-bit protected mode.", 0
; To fill the 512-byte space,
; we'll use zero for padding.
times 510-($-$$) db 0
; What's the magic number?
; Of course it's 0xAA55!
dw 0xAA55