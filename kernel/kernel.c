/* Naka-chan - The OS kernel!
   --------------------------------
   Finally, the heart of our OS!
   I present you... Naka-chan!
   Code: Yuuki Sanada
*/
// Let's call our textmode routines...
#include "../drivers/screen.h"
// And here's our main function!
// Don't mind, it's a bit barebones by now.
void kernel_main() {
    clear_screen();
    kprint_at("Testing, testing...", 0, 0);
    kprint("\nAw yiss, babe! It works!\n");
    kprint_at("h", 45, 24);
    kprint_at("Welcome to yuuOS", 30, 11);
}