#include "GDT.h"

#include "../Framebuffer/kPrintf.h"

struct GDTData
{
   uint16_t limit_low;           // The lower 16 bits of the limit.
   uint16_t base_low;            // The lower 16 bits of the base.
   uint8_t  base_middle;         // The next 8 bits of the base.
   uint8_t  access;              // Access flags, determine what ring this segment can be used in.
   uint8_t  granularity;		// Flags and 
   uint8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct GDTData GDTData;

struct GDT
{
	GDTData null;
	GDTData kernelCode;
	GDTData kernelData;
	GDTData userCode;
	GDTData userData;
	//GDTData TSS;
}
 __attribute__((packed));
typedef struct GDT GDT;

struct GDTDescriptor
{
	uint16_t size;
	uint64_t offset;
}__attribute__((packed));
typedef struct GDTDescriptor GDTDescriptor;

GDT gdt;
GDTDescriptor gdtDescriptor;

// GDT.asm
extern void gdt_set(GDTDescriptor* gdtDescriptor);

static void gdt_set_vals(GDTData* data, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	data->base_low    = (base & 0xFFFF);
	data->base_middle = (base >> 16) & 0xFF;
	data->base_high   = (base >> 24) & 0xFF;
 
	data->limit_low   = (limit & 0xFFFF);
	data->granularity = (limit >> 16) & 0x0F;
 
	data->granularity |= gran & 0xF0;
	data->access      = access;
}

void gdt_init()
{
	// #TODO userspace will need more entries
	gdt_set_vals(&gdt.null, 0, 0, 0, 0);                // Null segment
	gdt_set_vals(&gdt.kernelCode, 0, 0xFFFFFFFF, 0x9A, 0xAF); // Kernel code segment
	gdt_set_vals(&gdt.kernelData, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel data segment
	gdt_set_vals(&gdt.userCode, 0, 0xFFFFFFFF, 0xFA, 0xAF); // User data segment
	gdt_set_vals(&gdt.userData, 0, 0xFFFFFFFF, 0xF2, 0xAF); // User data segment
	//gdt_set_vals(&gdt.TSS, 0, 0xFFFFFFFF, 0x89, 0x0F); // User data segment
 
	gdtDescriptor.size = sizeof(GDT) - 1;
	gdtDescriptor.offset = (uint64_t)&gdt;

	gdt_set(&gdtDescriptor);

	kPrintf("GDT initialized!\n");
}
