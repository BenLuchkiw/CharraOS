#include "IDT.h"

#include "interrupts.h"
#include "../Framebuffer/kPrintf.h"

#include <stdint.h>

#define INTERRUPT_GATE 	0x8e
#define TRAP_GATE 		0x8f

struct IDTData
{
   uint16_t offset0;			// offset bits 0..15
   uint16_t selector;			// a code segment selector in GDT or LDT
   uint8_t  IST;				// bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t  typeAndAttributes;	// gate type, dpl, and p fields
   uint16_t offset1;			// offset bits 32..63
   uint32_t offset2;			// offset bits 16..31
   uint32_t zero;				// reserved
}__attribute__((packed));
typedef struct IDTData IDTData;

struct IDTDescriptor
{
	uint16_t size;
	uint64_t offset;
}__attribute__((packed));
typedef struct IDTDescriptor IDTDescriptor;

static IDTDescriptor idtDescriptor;
__attribute__((aligned(0x10))) 
static IDTData idtTable[256] = { 0 };

void idt_init_entry(uint8_t index, uint64_t offset, uint8_t gateType)
{
	idtTable[index].offset0 			= offset & 0xffff;
	idtTable[index].offset1 			= (offset >> 16) & 0xffff;
	idtTable[index].offset2 			= (offset >> 32) & 0xffffffff;
	idtTable[index].selector			= 0x08;
	idtTable[index].IST					= 0;
	idtTable[index].typeAndAttributes	= gateType;
	idtTable[index].zero 				= 0;
}

void idt_init()
{	
	idtDescriptor.size = sizeof(idtTable) - 1;
	idtDescriptor.offset = (uint64_t)idtTable;

	for(int i = 0; i < 32; i++)
	{
		idt_init_entry(i, (uint64_t)interupt_general_handler, INTERRUPT_GATE);
	}

	idt_init_entry(0x0e, (uint64_t)interrupt_page_fault_handler, INTERRUPT_GATE);

	__asm__ volatile ("lidt %0" : : "m"(idtDescriptor)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag

	kPrintf("IDT initialized!\n");
}