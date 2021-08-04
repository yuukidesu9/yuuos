#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "textmode.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../libc/stdio.h"
#include "../kernel/kernel.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define CAPSLOCK 0x3A

static char key_buffer[256];
static int buffersize = 0;

#define SC_MAX 58
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar", "CapsLock"};
const char sc_ascii[] = { '\0', '\0', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '\0', '\0', 'q', 'w', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '[', ']', '0', '\0', 'a', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', ';', '\'', '`', '\0', '\\', 'z', 'x', 'c', 'v', 
        'b', 'n', 'm', ',', '.', '/', '\0', '\0', '\0', ' ', '\0'};
const char sc_ascii_caps[] = { '\0', '\0', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '\0', '\0', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '\0', '\0', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '\0', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '\0', '\0', '\0', ' ', '\0'};
const char sc_ascii_shift[] = { '\0', '\0', '!', '@', '#', '$', '%', '^',     
    '&', '*', '(', ')', '_', '+', '\0', '\0', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '{', '}', '\0', '\0', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ':', '\"', '~', '\0', '|', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', '<', '>', '?', '\0', '\0', '\0', ' ', '\0'};

static int isCaps;
static int isShift;

static void keyboard_callback(registers_t regs) {
    // The PIC leaves us the scancode in port 0x60
    u8 scancode = inb(0x60);
    /* For scancode debug purposes:
    
    char sc_hex = '\0';
    hex_to_ascii((int)scancode, sc_hex);
    append(sc_hex, '\n');
    printf(sc_hex);
    
    */
    char letter;
    // Left/Right Shift press
    if ((scancode == 0x36) || (scancode == 0x2A)){
        isShift = 1;
    }
    // Left/Right Shift release
    if ((scancode == 0xB6) || (scancode == 0xAA)){
        isShift = 0;
    }
    if (scancode == CAPSLOCK){
        if(isCaps){
            isCaps = 0;
        }
        else{
            isCaps = 1;
        }
    }
    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) {
        buffersize--;
        if(buffersize >= 0){
            backspace(key_buffer);
            kprint_backspace();
        }
    } else if (scancode == ENTER) {
        printf("\n");
        user_input(key_buffer);
        key_buffer[0] = '\0';
        buffersize = 0;
    } else {
        if(isCaps){
            letter = sc_ascii_caps[(int)scancode];
        }
        else if(isShift){
            letter = sc_ascii_shift[(int)scancode];
        }
        else{
            letter = sc_ascii[(int)scancode];
        }
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        buffersize++;
        printf(str);
    }
    UNUSED(regs);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}