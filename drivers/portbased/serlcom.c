#include "..\..\cpu\ioports.h"
#include "serlcom.h"


#define SERIAL_LINE_HIGH_THEN_LOW 0x80 //First the highest 8 bits, then the lowest 8 bits in the data port

void serial_set_baud_rate(u16 com_port, u16 divisor);
void serial_configure_line(u16 com_port);
int serial_is_transmit_fifo_empty(u32 com_port);
// Set baud rate in a certain port.

// com_port is the port to set up.
// divisor is the divisor
void serial_set_baud_rate(u16 com_port, u16 divisor){
    outb(SERIAL_LINE_COMMAND_PORT(com_port), SERIAL_LINE_HIGH_THEN_LOW);
    outb(SERIAL_DATA_PORT(com_port), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com_port), divisor & 0x00FF);
}
// Configures line for a given serial port.

// com_port is the port to set up.
void serial_configure_line(u16 com_port){
    outb(SERIAL_LINE_COMMAND_PORT(com_port), 0x03);
}

//Check if the transmit FIFO is empty.
int serial_is_transmit_fifo_empty(u32 com_port){
    return inb(SERIAL_LINE_STATUS_PORT(com_port)) & 0x20;
}
// There we go!

void serial_write(char *buffer, unsigned int length) {
  serial_set_baud_rate(SERIAL_COM1_BASE, 3);
  serial_configure_line(SERIAL_COM1_BASE);

  unsigned int i;
  for (i=0; i<length; i++) {
    while (!serial_is_transmit_fifo_empty(SERIAL_COM1_BASE)){
        outb(SERIAL_DATA_PORT(SERIAL_COM1_BASE), buffer[i]);
    }
  }
}