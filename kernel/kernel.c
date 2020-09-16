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
    kprint_at("h", 1, 6);
    kprint_at("This text spans multiple lines", 75, 10);
    kprint_at("There is a line\nbreak", 0, 20);
    kprint("There is a line\nbreak");
    kprint_at("What happens when we run out of space?", 45, 24);
}