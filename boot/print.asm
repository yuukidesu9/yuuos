; Purin-chan - Screen printer
; --------------------------------
; It's Doku's nerdy sister with
; glasses who likes to type text
; in the screen.
; Code: Yuuki Sanada
; --------------------------------
; Let's put some stuff ova' here!
print:
    pusha
    
start:
    ; We pick the base address for the
    ; string (which is inside BX),
    ; put it into AL...
    mov al, [bx]
    ; ..until AL equals zero (EOF).
    cmp al, 0
    je done
    ; Meanwhile, we make it print!
    mov ah, 0x0e
    ; Interrupts galore!
    int 0x10
    ; Then we increment BX...
    add bx, 1
    ; ...and get back to the start of the loop.
    jmp start
    
done:
    popa
    ret
    
print_nl:
    pusha
    mov ah, 0x0E
    ; We put a LF (line feed)...
    mov al, 0x0A
    int 0x10
    ; ...and a CR (carriage return)...
    mov al, 0x0D
    int 0x10
    ; ...and finish.
    popa
    ret
  
; I'm too lazy to write a description
; for this part.
; I'll do it later. I promise. ;3
print_hex:
    pusha
    mov cx, 0
    
hex_loop:
    cmp cx, 4
    je end
    mov ax, dx
    and ax, 0x000f
    add al, 0x30
    cmp al, 0x39
    jle step2
    add al, 7

step2:
    mov bx, HEX_OUT + 5
    sub bx, cx
    mov [bx], al
    ror dx, 4
    add cx, 1
    jmp hex_loop

end:
    mov bx, HEX_OUT
    call print
    popa
    ret

HEX_OUT:
    db '0x0000',0
