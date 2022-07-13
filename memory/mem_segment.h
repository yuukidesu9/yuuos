#ifndef MEM_SEGMENT_H
#define MEM_SEGMENT_H

#include "../backbone/typedef.h"

struct GDT {
    u16 size;
    u32 address;
} __attribute__((packed));

struct GDTDescriptor{
    u16 limit_low;
    u16 base_low;
    u8 base_middle;
    u8 access_byte;
    u8 limits_and_flags;
    u8 base_high;
} __attribute__((packed));



#endif