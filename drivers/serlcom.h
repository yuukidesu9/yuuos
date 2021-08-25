#ifndef SERLCOM_H
#define SERLCOM_H

#include "../cpu/type.h"

void serial_set_baud_rate(u16 com_port, u16 divisor);
void serial_configure_line(u16 com_port);
int serial_is_transmit_fifo_empty(u32 com_port);

#endif