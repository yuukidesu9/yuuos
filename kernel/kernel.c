/* Naka-chan - The OS kernel!
   --------------------------------
   Finally, the heart of our OS!
   I present you... Naka-chan!
   Code: Yuuki Sanada
*/
// Let's call our textmode routines...
#include "../drivers/screen.h"
// ...our interrupt handling routines...
#include "../cpu/idt.h"
#include "../cpu/isr.h"
// ..and our utilities.
#include "util.h"
// And here's our main function!
// Don't mind, it's a bit barebones by now.

void kernel_main() {
    clear_screen();
    kprint_at("Testing, testing...", 0, 0);
    kprint("\nAw yiss, babe! It works!\n");
    kprint_at("h", 45, 24);
    kprint_at("Welcome to yuuOS", 30, 11);
    kprint_at("This text forces the kernel to scroll. Row 0 will disappear. ", 60, 24);
    kprint("And with this text, the kernel will scroll again, and row 1 will disappear too!");
    isr_install();
    /* Test some interrupts */
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}