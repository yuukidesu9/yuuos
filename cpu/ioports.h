#ifndef INCLUDE_IOPORTS_H
#define INCLUDE_IOPORTS_H

#include "..\backbone\typedef.h"

/** outb:
 *  Sends a byte to the given CPU I/O port. Defined in io.s
 *
 *  @param port I/O port address to send the data to
 *  @param data Byte to send to the I/O port
 */
void outb(u16 port, u8 data);

/** inb:
 *  Reads a byte from a CPU I/O port.
 *
 *  @param  port I/O port address
 *  @return      The read byte
 */
u8 inb(u16 port);

#endif