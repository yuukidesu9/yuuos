#include "../../cpu/ioports.h"

#define KEYBOARD_DATA_PORT 0x60

unsigned char keyboard_read_scan_code(void)
{
	return inb(KEYBOARD_DATA_PORT);
}

unsigned char keyboard_scan_code_to_ascii(unsigned char scan_code)
{
	unsigned char ascii[256] =
	{
		0x0, 0x0, '1', '2', '3', '4', '5', '6',		// 0 - 7
		'7', '8', '9', '0', '-', '=', 0x0, 0x0,		// 8 - 15
		'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',		// 16 - 23
		'o', 'p', '[', ']', '\n', 0x0, 'a', 's',	// 24 - 31
		'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',		// 32 - 39
		'\'', '`', 0x0, '\\', 'z', 'x', 'c', 'v',	// 40 - 47
		'b', 'n', 'm', ',', '.', '/', 0x0, '*',		// 48 - 55
		0x0, ' ', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,		// 56 - 63
		0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, '7',		// 64 - 71
		'8', '9', '-', '4', '5', '6', '+', '1',		// 72 - 79
		'2', '3', '0', '.'				// 80 - 83
	};

	return ascii[scan_code];
}
