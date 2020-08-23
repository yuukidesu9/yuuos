; Yomite-chan - Disk reader
; --------------------------------
; A boot sector reader. It helps
; Dokusha-chan, so to say.
; Let's pretend it's her twin
; sister.
; Code: Yuuki Sanada
; --------------------------------
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
    jmp disk_loop
    
sectors_error:
    ; We print an error message.
    mov bx, SECTORS_ERR
    call print
    
; Infinite loop time!
disk_loop:
    jmp $

DISK_ERR:
    db "ERROR: disk read error", 0

SECTORS_ERR:
    db "ERROR: incorrect number of read sectors", 0