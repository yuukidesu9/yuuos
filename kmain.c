/* The OS kernel!
   --------------------------------
   Finally, the heart of our OS!
   Code: Yuuki Sanada
*/
// Let's call our routines.
#include "drivers/portbased/textmode.h"
#include "drivers/portbased/serlcom.h"
#include "drivers/intbased/keyboard.h"
//#include "libc/stdio.h"
#include "libc/string.h"
#include "libc/mem.h"
//#include "kmain.h"
#include "cpu/interrupts.h"
#include "cpu/ioports.h"
#include "memory/mem_segment.h"
// And here's our main function!
// Don't mind, it's a bit barebones by now.

//void quit_sys();

char test[] = "yuuOS framebuffer test";

void loader_main() {
    //clear_screen();
    move_cursor(6*80);
    writestring(test, sizeof(test));
    serial_send(test, sizeof(test));
    segment_install_gdt();
    //interrupts_install_idt();
    //kprint_at("Welcome to yuuOS Minimal!\nYou are on loader mode.\n", 29, 11);
    /*writestring("Welcome to yuuOS Minimal!\nYou are on loader mode.\n", 50);
    writestring("\n                         .d88888b.  .d8888b.\n", 46);
    writestring("                        d88P\" \"Y88bd88P  Y88b\n", 46);
    writestring("                        888     888Y88b.\n", 41);
    writestring("888  888888  888888  888888     888 \"Y888b.\n", 44);
    writestring("888  888888  888888  888888     888    \"Y88b.\n", 46);
    writestring("888  888888  888888  888888     888      \"888\n", 46);
    writestring("Y88b 888Y88b 888Y88b 888Y88b. .d88PY88b  d88P\n", 46);
    writestring("\"Y88888 \"Y88888 \"Y88888 \"Y88888P\"  \"Y8888P\"\n", 44);
    writestring("     888\n", 9);
    writestring("Y8b d88P                    The foxy guy's OS\n", 46);
    writestring("\"Y88P\"\n\n", 8);
    writestring("Lead development: YuukiDesu9\n", 29);
    //isr_install();
    //irq_install();
    //initialize serial port here
    serial_set_baud_rate(0x3F8, 0x01); //Set rate to 115,200 baud
    serial_configure_line(0x3F8);
    segment_install_gdt();
    interrupts_install_idt();*/
}
    //if(serial_is_transmit_fifo_empty(0x3F8) == 0){
        //do the thing...
    //}
    //printf("Type 'help' for available commands. Lowercase only.\n> ");
//}

/*void user_input(char *input) {
    if (strcmp(input, "end") == 0) {
        quit_sys();
    } else if (strcmp(input, "quit") == 0) {
        quit_sys();
    } else if (strcmp(input, "exit") == 0) {
        quit_sys();
    } else if (strcmp(input, "page") == 0) {
        unsigned int phys_addr;
        unsigned int page = malloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        printf("Memory page: ");
        printf(page_str);
        printf("\nPhysical address: ");
        printf(phys_str);
        printf("\n");
    }
    else if (strcmp(input, "help") == 0){
        printf("\nAvailable commands:\nabout / info / uname - Shows OS info.\nclear - Clear screen.\n");
        printf("exit / quit / end - Shuts down.\npage - Requests a memory page.\n");
    }
    else if (strcmp(input, "name") == 0){
        printf("Hello there, user! Hope you have a great day!");
    }
    else if (strcmp(input, "about") == 0){
        about();
    }
    else if (strcmp(input, "info") == 0) {
        about();
    }
    else if (strcmp(input, "clear") == 0){
        clear_screen();
    }
    else if ((strcmp(input, "uname") == 0)){
        printf("\n");
        printf(SYSKERNEL);
        printf(" ");
        printf(KERNELVER);
        printf(" ");
        printf(SYSARCH);
    }
    else {
        printf(" is not a recognizable command. Try another one.");
    }
    printf("\n> ");
}

void about(){*/

    //printf("Special thanks to: cfenollosa, AlgorithMan.de, wuffuccino and DuqueDuk");
    

/*}

void quit_sys(){
    clear_screen();
    kprint_at("CPU halted. Now you can manually shut down. Bye!", 11, 13);*/
    //asm volatile("hlt");
