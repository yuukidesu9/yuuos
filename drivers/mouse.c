#include "mouse.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"

static void mouse_callback(registers_t regs){
    char offset = 0;
    char buffer[3];
    char buttons = 0;
    char status = port_byte_in(0x64);
    if(!(status & 0x20)){
        asm("nop");
    }
    offset = (offset + 1) % 3;
    if(offset == 0){
        if(buffer[1] != 0 || buffer[2] != 0){
            //Move the mouse on screen.
        }
    }
    for(int i = 0; i < 3; i++){
        if((buffer[0] & (0x1<<i)) != (buttons & (0x1<<i))){
            if(buttons & (0x1<<i)){
                //Click or keep button pressed
            }
            else{
                //Click end or release button
            }
        }
    }
    buttons = buffer[0];
    //Placeholder function.
    UNUSED(regs);
}

void init_mouse() {
    //So, basically, what we're going to do
    //to activate the mouse is:
    // - Handle our IRQ 12
    // - Write byte 0xA8 in PIC's port 0x64
    // - Write byte 0x20 in PIC's port 0x64
    // - Read status byte from PIC's port 0x60
    // - Write byte 0x60 in PIC's port 0x64
    // - Write status byte in PIC's port 0x60
    // - Write byte 0x40 in PIC's port 0x64
    // - Write byte 0xF4 in PIC's port 0x60
    // - then read from PIC's port 0x60.
    //Simple, right?
   register_interrupt_handler(IRQ12, mouse_callback);
   port_byte_out(0x64, 0xA8);
   port_byte_out(0x64, 0x20);
   char status = port_byte_in(0x60) | 2;
   port_byte_out(0x64, 0x60);
   port_byte_out(0x60, status);
   port_byte_out(0x64, 0x40);
   port_byte_out(0x60, 0xF4);
   port_byte_in(0x60);
}
