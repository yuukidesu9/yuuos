#ifndef INCLUDE_IOPORTS_H
#define INCLUDE_IOPORTS_H

/** outb:
 *  Sends a byte to the given CPU I/O port. Defined in io.s
 *
 *  @param port I/O port address to send the data to
 *  @param data Byte to send to the I/O port
 */
void outb(unsigned short port, unsigned char data);

/** inb:
 *  Reads a byte from a CPU I/O port.
 *
 *  @param  port I/O port address
 *  @return      The read byte
 */
unsigned char inb(unsigned short port);

#endif
