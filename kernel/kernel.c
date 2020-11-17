/* Naka-chan - The OS kernel!
   --------------------------------
   Finally, the heart of our OS!
   I present you... Naka-chan!
   Code: Yuuki Sanada
*/
// Let's call our routines.
#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../libc/stdio.h"
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
    printf("Type 'help' for available commands. Lowercase only.\n>");
}

void user_input(char *input) {
    if (strcmp(input, "end") == 0) {
        clear_screen();
        kprint_at("CPU halted. Now you can manually shut down. Bye!", 9, 13);
        asm volatile("hlt");
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
        printf("\nAvailable commands:\nabout - Shows OS info.\nclear - Clear screen.\ncpuid - Identifies CPU. (TODO)\n");
        printf("end - Shuts down.\npage - Requests a memory page.\n");
    }
    else if (strcmp(input, "name") == 0){
        printf("Hello there, user! Hope you have a great day!");
    }
    else if (strcmp(input, "about") == 0){
        about();
    }
    else if (strcmp(input, "clear") == 0){
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
    printf("CPU.\n\nVersion 0.1.2\nCompile date: Nov 17, 2020\n\nLead development: YuukiDesu9\n");
    printf("Special thanks to: cfenollosa, AlgorithMan.de, wuffuccino and DuqueDuk");
}

void vendor(){
    char vendstr[12];
    int vendor[3];
    __asm__("mov $0x0, %eax\n\t");
    __asm__("cpuid\n\t");
    __asm__("mov %%ebx, %0\n\t":"=r" (vendor[0]));
    __asm__("mov %%edx, %0\n\t":"=r" (vendor[1]));
    __asm__("mov %%ecx, %0\n\t":"=r" (vendor[2]));
    vendstr[0] = vendor[0] & 0xFF;
    vendstr[1] = (vendor[0] >> 8) & 0xFF;
    vendstr[2] = (vendor[0] >> 16) & 0xFF;
    vendstr[3] = (vendor[0] >> 24) & 0xFF;
    vendstr[4] = vendor[1] & 0xFF;
    vendstr[5] = (vendor[1] >> 8) & 0xFF;
    vendstr[6] = (vendor[1] >> 16) & 0xFF;
    vendstr[7] = (vendor[1] >> 24)& 0xFF;
    vendstr[8] = vendor[2] & 0xFF;
    vendstr[9] = (vendor[2] >> 8) & 0xFF;
    vendstr[10] = (vendor[2] >> 16) & 0xFF;
    vendstr[11] = (vendor[2] >> 24) & 0xFF;
    backspace(vendstr);
    backspace(vendstr);
    printf(vendstr);
}

void cpubrand(){
    pickStr(1);
    pickStr(2);
    pickStr(3);
    printf("\n");
}

void pickStr(int eaxValue){
    char brandstr[16];
    int brand[4];
    if (eaxValue == 1) {
    __asm__("mov $0x80000002 , %eax\n\t");
    }
    else if (eaxValue == 2) {
        __asm__("mov $0x80000003 , %eax\n\t");
    }
    else if (eaxValue == 3) {
        __asm__("mov $0x80000004 , %eax\n\t");
    }
    __asm__("cpuid\n\t");
    __asm__("mov %%eax, %0\n\t":"=r" (brand[0]));
    __asm__("mov %%ebx, %0\n\t":"=r" (brand[1]));
    __asm__("mov %%ecx, %0\n\t":"=r" (brand[2]));
    __asm__("mov %%edx, %0\n\t":"=r" (brand[3]));
    brandstr[0] = brand[0] & 0xFF;
    brandstr[1] = (brand[0] >> 8) & 0xFF;
    brandstr[2] = (brand[0] >> 16) & 0xFF;
    brandstr[3] = (brand[0] >> 24) & 0xFF;
    brandstr[4] = brand[1] & 0xFF;
    brandstr[5] = (brand[1] >> 8) & 0xFF;
    brandstr[6] = (brand[1] >> 16) & 0xFF;
    brandstr[7] = (brand[1] >> 24) & 0xFF;
    brandstr[8] = brand[2] & 0xFF;
    brandstr[9] = (brand[2] >> 8) & 0xFF;
    brandstr[10] = (brand[2] >> 16) & 0xFF;
    brandstr[11] = (brand[2] >> 24) & 0xFF;
    brandstr[12] = brand[3] & 0xFF;
    brandstr[13] = (brand[3] >> 8) & 0xFF;
    brandstr[14] = (brand[3] >> 16) & 0xFF;
    brandstr[15] = (brand[3] >> 24) & 0xFF;
    printf(brandstr);
}