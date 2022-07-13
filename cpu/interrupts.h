#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include "../backbone/typedef.h"

struct IDT 
{
	u16 size;
	u32 address;
} __attribute__((packed));

struct IDTDescriptor {
	/* The lowest 32 bits */
	u16 offset_low; // offset bits 0..15
	u16 segment_selector; // a code segment selector in GDT or LDT
	
	/* The highest 32 bits */
	u8 reserved; // Just 0.
	u8 type_and_attr; // type and attributes
	u16 offset_high; // offset bits 16..31
} __attribute__((packed));

void interrupts_install_idt();

// Wrappers around ASM.
void load_idt(u32 idt_address);
void interrupt_handler_33();
//void interrupt_handler_14();

struct cpu_state {
	u32 eax;
	u32 ebx;
	u32 ecx;
	u32 edx;
	u32 ebp; 
	u32 esi; 
	u32 edi; 
} __attribute__((packed));

struct stack_state {
	u32 error_code;
	u32 eip;
	u32 cs;
	u32 eflags;
} __attribute__((packed));

void interrupt_handler(struct cpu_state cpu, u32 interrupt, struct stack_state stack);


#endif