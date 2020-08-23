[org 0x7C00]
; Dokusha-chan - Boot sector
; --------------------------------
; A simple cute boot sector for
; the YuuOS floppy microkernel.
; Code: Yuuki Sanada
; --------------------------------
    ; The AL register can store a
    ; string to show in video.
    ; The 0x10 interrupt is a video
    ; interrupt, which prints the
    ; stuff stored in AL.
    mov bx, GREET
    call print
    call print_nl
    ; Let's put the stack far from us,
    ; right?
    mov bp, 0x8000
    mov sp, bp
    mov bx, 0x9000
    ; Now read two sectors:
    mov dh, 2
    call disk_load
    ; Here, we'll read the first word.
    mov dx, [0x9000]
    call print_hex
    call print_nl
    ; And here, the second sector.
    mov dx, [0x9000 + 512]
    call print_hex
    ; TTY mode.
    mov ah, 0x0E
    
    ; We'll get in an infinite loop.
    ; Yes, intentionally.
    jmp $
; We'll append the disk reading
; part of our code.
%include "disksect.asm"
%include "print.asm"
; To fill the 512-byte space,
; we'll use zero for padding.
; Here we'll store some text.
    ; How about a 'Hello!'?
    ; P.S.: Strings have to finish
    ; with a null byte, that's why
    ; the zero is after the string
    ; without quotes.
GREET:
    db 'Hello, world...', 0
    
times 510-($-$$) db 0
; What's the magic number?
; Oh yes, it's 0xAA55 in the
; DW register.
dw 0xAA55
; Filling our other sectors!
times 256 dw 0xDADA
times 256 dw 0xFACE