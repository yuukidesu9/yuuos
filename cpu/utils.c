#include "utils.h"
#include "../libc/stdio.h"
#include "../libc/string.h"
#include "../drivers/textmode.h"

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
    switch(eaxValue){
        case 1:
            __asm__("mov $0x80000002 , %eax\n\t");
            break;
        case 2:
            __asm__("mov $0x80000003 , %eax\n\t");
            break;
        case 3:
            __asm__("mov $0x80000004 , %eax\n\t");
            break;
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