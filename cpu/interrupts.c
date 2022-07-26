#include "interrupts.h"
#include "pic.h"
#include "ioports.h"

#include "../drivers/intbased/keyboard.h"
#include "../drivers/portbased/serlcom.h"

//The amount of interrupt descriptors.
#define INTERRUPTS_DESCRIPTOR_COUNT 256
// Keyboard interrupt number
#define INTERRUPTS_KEYBOARD 33
//#define INTERRUPTS_PAGING 14

struct IDTDescriptor idt_descriptor[INTERRUPTS_DESCRIPTOR_COUNT];
struct IDT idt;

void interrupts_init_descriptor(int index, unsigned int address)
{
	idt_descriptor[index].offset_high = (address >> 16) & 0xFFFF; // High offset bits, 0..15 (31-16, MSB)
	idt_descriptor[index].offset_low = (address & 0xFFFF); // Low offset bits, 16..31 (15-0, MSB)

	idt_descriptor[index].segment_selector = 0x08; // The second (code) segment selector in GDT: one segment is 64b.
	idt_descriptor[index].reserved = 0x00; // Reserved thingy for the descriptor.

	/*
       Type and attributes for the descriptor:
       
	   Bit:     | 31              16 | 15 | 14 13 | 12 | 11 10 9 8   | 7 6 5 | 4 3 2 1 0 |
	   Content: | offset high        | P  | DPL   | S  | D and G     | 0 0 0 | reserved  |
		P	If the handler is present in memory or not (1 = present, 0 = not present). Set to 0 for unused interrupts or for Paging.
		DPL	Descriptor Privilige Level, the privilege level the handler can be called from (0, 1, 2, 3).
		S	Storage Segment. Set to 0 for interrupt gates.
		D	Size of gate, (1 = 32 bits, 0 = 16 bits).
        G   GateType (0b110 = Interrupt gate)
	*/
    // P | DPL | SS, D and G
	idt_descriptor[index].type_and_attr =	(0x01 << 7) | (0x00 << 6) | (0x00 << 5) | 0xe;
}

void interrupts_install_idt()
{
	interrupts_init_descriptor(INTERRUPTS_KEYBOARD, (unsigned int) interrupt_handler_33);
	//interrupts_init_descriptor(INTERRUPTS_PAGING, (unsigned int) interrupt_handler_14);


	idt.address = (int) &idt_descriptor;
	idt.size = sizeof(struct IDTDescriptor) * INTERRUPTS_DESCRIPTOR_COUNT;
	load_idt((int) &idt);

	/*pic_remap(PIC_PIC1_OFFSET, PIC_PIC2_OFFSET);*/
	pic_remap(PIC_1_OFFSET, PIC_2_OFFSET);
}

void interrupt_handler(__attribute__((unused)) struct cpu_state cpu, unsigned int interrupt, __attribute__((unused)) struct stack_state stack)
{
	unsigned char scan_code;
	unsigned char ascii;

	switch (interrupt){
		case INTERRUPTS_KEYBOARD:

			scan_code = keyboard_read_scan_code();

			if (scan_code <= KEYBOARD_MAX_ASCII) {
				ascii = keyboard_scan_code_to_ascii(scan_code);
				serial_set_baud_rate(SERIAL_COM1_BASE, 4);
				serial_configure_line(SERIAL_COM1_BASE);
				char str[1];
				str[0] = ascii;
				serial_send(str, 1);
			}

			pic_acknowledge(interrupt);

			break;
		
		/*case INTERRUPTS_PAGING:
			page_fault();	
			break;
		default:
			break;
        */
    }
}
