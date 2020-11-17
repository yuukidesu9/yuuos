#ifndef PORTS_H
#define PORTS_H

#include "../cpu/type.h"

unsigned char inb (u16 port);
void outb (u16 port, u8 data);
unsigned short inw (u16 port);
void outw (u16 port, u16 data);
unsigned int indw (u32 port);
void outdw (u32 port, u32 data);

#endif
