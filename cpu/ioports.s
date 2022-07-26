global outb ; Make both functions global so we
global inb  ; can use them in our C code

outb:
    mov dx, [esp + 4] ; Port to send data to
    mov al, [esp + 8] ; Data to be sent into the AL register
    out dx, al        ; Send the byte (OUTPUT from DX to where AL points to)
    ret               ; Return the function

inb:
    mov dx, [esp + 4] ; Port to receive the data from
    in al, dx         ; Receive the data (IN from DX to AL)
    ret               ; Return the function