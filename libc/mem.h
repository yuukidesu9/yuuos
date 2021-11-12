#ifndef MEM_H
#define MEM_H

#include "..\backbone\typedef.h"

void memcpy(u8 *source, u8 *dest, int nbytes);
void memset(u8 *dest, u8 val, u32 len);

// At this stage there is a 'free' implemented.
// In a very clumsy way, but it's there.
u32 malloc(u32 size, int align, u32 *phys_addr);

#endif
