/* Naka-chan - The OS kernel!
   --------------------------------
   Finally, the heart of our OS!
   I present you... Naka-chan!
   Code: Yuuki Sanada
*/
// Let's call our routines.
#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "kernel.h"
// And here's our main function!
// Don't mind, it's a bit barebones by now.

void kernel_main() {
    clear_screen();
    kprint_at("Welcome to yuuOS!\n", 29, 11);
    isr_install();
    irq_install();
    kprint("Version 0.1\nType HELP for available commands.\n>");
}

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        clear_screen();
        kprint_at("CPU halted. Now you can manually shut down. Bye!", 9, 13);
        asm volatile("hlt");
    } else if (strcmp(input, "PAGE") == 0) {
        u32 phys_addr;
        u32 page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Memory page: ");
        kprint(page_str);
        kprint("\nPhysical address: ");
        kprint(phys_str);
        kprint("\n");
    }
    else if (strcmp(input, "HELP") == 0){
        kprint("\nAvailable commands:\nEND - Shuts down.\n");
        kprint("PAGE - Requests a memory page.\nVER - Shows current version.\n");
    }
    else if (strcmp(input, "NAME") == 0){
        kprint("Hello there, user! Hope you have a great day!");
    }
    else if (strcmp(input, "ABOUT") == 0){
        about();
    }
    /*else if (strcmp(input, "CPUID") == 0){
        cpuid();
    }*/
    else {
        kprint(input);
        kprint(" is not a recognizable command. Try another one.");
    }
    kprint("\n>");
}

void about(){
    kprint("\n                         .d88888b.  .d8888b.\n");
    kprint("                        d88P\" \"Y88bd88P  Y88b\n");
    kprint("                        888     888Y88b.\n");
    kprint("888  888888  888888  888888     888 \"Y888b.\n");
    kprint("888  888888  888888  888888     888    \"Y88b.\n");
    kprint("888  888888  888888  888888     888      \"888\n");
    kprint("Y88b 888Y88b 888Y88b 888Y88b. .d88PY88b  d88P\n");
    kprint("\"Y88888 \"Y88888 \"Y88888 \"Y88888P\"  \"Y8888P\"\n");
    kprint("     888\n");
    kprint("Y8b d88P                    The foxy guy's OS\n");
    kprint("\"Y88P\"\n\n");
    kprint("Version 0.1 beta 2\nCompile date: Nov 5, 2020\n\nLead development: YuukiDesu9\n");
    kprint("Special thanks to: cfenollosa, AlgorithMan.de, wuffuccino and DuqueDuk");
}

/*void cpuid(){
    
}*/