#include "mem_segment.h"

#define SEGMENT_DESCRIPTOR_COUNT 3

#define SEGMENT_BASE 0
#define SEGMENT_LIMIT 0xFFFFF

#define SEGMENT_CODE_TYPE 0x9A
#define SEGMENT_DATA_TYPE 0x92

void segment_init_descriptor(int index, unsigned int base_addr, unsigned int limit, unsigned char access_byte, unsigned char flags);
void segment_install_gdt();
/* Flags

x x x x
3 2 1 0

0. Available for system use (0 for no, 1 for yes)
1. Long Mode (0 for 16/32-bit, 1 for 64-bit)
2. Size (0 for 16-bit, 1 for 32-bit)
3. Granularity (0 for 1B-1MB, 1 for 4KB-4GB)

We're gonna make it:
- unavailable for system use (0 on the bit 0),
- as protected mode (0 on the bit 1),
- make it 32-bit (1 on the bit 2), and
- make it have 4kB control data for each page (1 on the bit 3).

So it's 1100, or 0x0C. */

#define SEGMENT_FLAGS 0x0C

static struct GDTDescriptor gdt_descriptors[SEGMENT_DESCRIPTOR_COUNT];

void segment_init_descriptor(int index, unsigned int base_addr, unsigned int limit, unsigned char access_byte, unsigned char flags){
    gdt_descriptors[index].base_low = base_addr & 0xFFFF;
    gdt_descriptors[index].base_middle = (base_addr >> 16) & 0xFF;
    gdt_descriptors[index].base_high = (base_addr >> 24) & 0xFF;

    gdt_descriptors[index].limit_low = limit & 0xFFFF;
    gdt_descriptors[index].limits_and_flags = (limit >> 16) & 0xF;
    gdt_descriptors[index].limits_and_flags |= (flags << 4) & 0xF0;

    gdt_descriptors[index].access_byte = access_byte;
}

void segment_install_gdt(){
    gdt_descriptors[0].base_low = 0;
    gdt_descriptors[0].base_middle = 0;
    gdt_descriptors[0].base_high = 0;
    gdt_descriptors[0].limit_low = 0;
    gdt_descriptors[0].access_byte = 0;
    gdt_descriptors[0].limits_and_flags = 0;
    //Null descriptor for GDT initialization.

    struct GDT* gdt_pointer = (struct GDT*)gdt_descriptors;
    gdt_pointer->address = (unsigned int)gdt_descriptors;
    gdt_pointer->size = (sizeof(struct GDTDescriptor) * SEGMENT_DESCRIPTOR_COUNT) - 1;

    segment_init_descriptor(1, SEGMENT_BASE, SEGMENT_LIMIT, SEGMENT_CODE_TYPE, SEGMENT_FLAGS); //Kernel code segment
    segment_init_descriptor(2, SEGMENT_BASE, SEGMENT_LIMIT, SEGMENT_DATA_TYPE, SEGMENT_FLAGS); //Kernel data segment

    segments_load_gdt(*gdt_pointer);
    segments_load_registers();
}
