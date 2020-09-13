/* Naka-chan - The OS kernel!
   --------------------------------
   Finally, the heart of our OS!
   I present you... Naka-chan!
   Code: Yuuki Sanada
*/
// Let's call our ports thingie...
#include "../drivers/ports.h"
// And here's our main function!
// Don't mind, it's still barebones by now.
void kernel_main() {
    // Screen cursor position: ask VGA control register (0x3d4) for bytes
    // 14 = high byte of cursor and 15 = low byte of cursor.
    port_byte_out(0x3d4, 14); // Requesting byte 14: high byte of cursor pos
    // Data is returned in VGA data register (0x3d5)
    int position = port_byte_in(0x3d5);
    position = position << 8; // high byte

    port_byte_out(0x3d4, 15); // requesting low byte
    position += port_byte_in(0x3d5);

    // VGA 'cells' consist of the character and its control data
    // e.g. 'white on black background', 'red text on white bg', etc.
    int offset_from_vga = position * 2;

    // Writing on the current cursor positionnnn
    char *vga = 0xb8000;
    vga[offset_from_vga] = 'h'; // Yo, people from IDh
    vga[offset_from_vga+1] = 0x0f; // White text on black background because I don't know how to change them colors~
}