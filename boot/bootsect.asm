[org 0x7C00]
; Dokusha-chan - Boot sector
; --------------------------------
; A simple cute boot sector for
; the YuuOS floppy microkernel.
; Code: Yuuki Sanada
; --------------------------------
; Here's our kernel offset.
KERNEL_OFFSET equ 0x1000
; The AL register can store a
; string to show in video.
; The 0x10 interrupt is a video
; interrupt, which prints the
; stuff stored in AL.
mov bx, GREET
call print
call print_nl
; Welp, time to load from the drive!
mov [BOOT_DRIVE], dl
; Let's put the stack far from us,
; right?
mov bp, 0x9000
mov sp, bp
mov bx, REALMODE
call print
call print_nl
; Now read two sectors:
mov dh, 2
; Now, sing with me!
; The itsy bitsy kernel
; was loaded into memory,
call load_kernel
; Then came protected mode
; to show it into the screen
call switch_protmode
; We'll get in an infinite loop.
; Yes, intentionally.
jmp $

; We'll append the disk reading
; part of our code.
%include "disksect.asm"
%include "print.asm"

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
    mov dh, 2
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
GREET:
    db "Hello, world!", 0
BOOT_DRIVE:
    db 0
REALMODE:
    db "Entering 16-bit real mode.", 0
KRNLLOAD:
    db "Loading kernel into memory.", 0
PROTMODE:
    db "Entering 32-bit protected mode.", 0
; To fill the 512-byte space,
; we'll use zero for padding.
times 510-($-$$) db 0
; What's the magic number?
; Of course it's 0xAA55!
dw 0xAA55