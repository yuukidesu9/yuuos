; Kerberos-chan - 32-bit switcher
; --------------------------------
; She switches our stuff to
; protected mode.
; Code: Yuuki Sanada
; --------------------------------
[bits 16]
switch_protmode:
    ; First things first: no interrupts
    cli
    ; Load our GDT descriptor.
    lgdt [gdt_descriptor]
    ; Set 32-bit mode in CR0 register!
    ; Yay!
    mov eax, cr0
    or eax, 0x1
    ; And jump to our code segment!
    jmp CODE_SEG
    call init_pm

; 32-bit is now working its magic!
[bits 32]
init_pm:
    mov ax, DATA_SEG
    ; Updating the segment registers...
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ; Update our stack...
    mov ebp, 0x900000
    mov esp, ebp
    ; And done!
    call begin_pm