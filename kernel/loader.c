/* Naka-chan - The OS kernel!
   --------------------------------
   Finally, the heart of our OS!
   I present you... Naka-chan!
   Code: Yuuki Sanada
*/
// Let's call our routines.
#include "../cpu/isr.h"
#include "../cpu/utils.h"
#include "../drivers/screen.h"
#include "../libc/stdio.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "loader.h"
// And here's our main function!
// Don't mind, it's a bit barebones by now.

void quit_sys();

void loader_main() {
    clear_screen();
    kprint_at("Welcome to yuuOS!\n", 29, 11);
    isr_install();
    irq_install();
    printf("Type 'help' for available commands. Lowercase only.\n>");
}

void user_input(char *input) {
    if (strcmp(input, "end") == 0) {
        quit_sys();
    } else if (strcmp(input, "quit") == 0) {
        quit_sys();
    } else if (strcmp(input, "exit") == 0) {
        quit_sys();
    } else if (strcmp(input, "page") == 0) {
        u32 phys_addr;
        u32 page = malloc(1000, 1, &phys_addr);
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
        printf("\nAvailable commands:\nabout / info - Shows OS info.\nclear - Clear screen.\n");
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
    } else if (strcmp(input, "clear") == 0){
        clear_screen();
    }
    else {
        printf(input);
        printf(" is not a recognizable command. Try another one.");
    }
    printf("\n>");
}

void about(){
    printf("\n                         .d88888b.  .d8888b.\n");
    printf("                        d88P\" \"Y88bd88P  Y88b\n");
    printf("                        888     888Y88b.\n");
    printf("888  888888  888888  888888     888 \"Y888b.\n");
    printf("888  888888  888888  888888     888    \"Y88b.\n");
    printf("888  888888  888888  888888     888      \"888\n");
    printf("Y88b 888Y88b 888Y88b 888Y88b. .d88PY88b  d88P\n");
    printf("\"Y88888 \"Y88888 \"Y88888 \"Y88888P\"  \"Y8888P\"\n");
    printf("     888\n");
    printf("Y8b d88P                    The foxy guy's OS\n");
    printf("\"Y88P\"\n\n");
    printf("Processor vendor: ");
    vendor();
    printf("\nyuuOS is running on a ");
    cpubrand();
    printf("CPU.\n\nVersion 0.2.1\nCompile date: Nov 27, 2020\n\nLead development: YuukiDesu9\n");
    printf("Special thanks to: cfenollosa, AlgorithMan.de, wuffuccino and DuqueDuk");
}

void quit_sys(){
    clear_screen();
    kprint_at("CPU halted. Now you can manually shut down. Bye!", 9, 13);
    asm volatile("hlt");
}