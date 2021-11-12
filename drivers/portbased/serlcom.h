#ifndef SERLCOM_H
#define SERLCOM_H

#include "..\..\backbone\typedef.h"

#define SERIAL_COM1_BASE 0x3F8 //COM1 serial base port

#define SERIAL_DATA_PORT(base) base
#define SERIAL_FIFO_COMMAND_PORT(base) base+2
#define SERIAL_LINE_COMMAND_PORT(base) base+3
#define SERIAL_MODEM_COMMAND_PORT(base) base+4
#define SERIAL_LINE_STATUS_PORT(base) base+5

#define SERIAL_LINE_HIGH_THEN_LOW 0x80 //First the highest 8 bits, then the lowest 8 bits in the data port

void serial_set_baud_rate(u16 com_port, u16 divisor);
void serial_configure_line(u16 com_port);

 /** serial_is_transmit_fifo_empty:
  *  Checks whether the transmit FIFO queue is empty or not for the given COM
  *  port.
  *
  *  @param  com The COM port
  *  @return 0 if the transmit FIFO queue is not empty
  *          1 if the transmit FIFO queue is empty
  */
int serial_is_transmit_fifo_empty(u32 com_port);

void serial_send(char *buffer, unsigned int length);

#endif