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
    clear_screen();
    move_cursor(6*80);
    writestring(test, sizeof(test));
    serial_send(test, sizeof(test));
    segment_install_gdt();
}
