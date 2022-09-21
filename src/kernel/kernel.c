#include "kernel.h"

#include "DescriptorTables/GDT.h"
#include "Interrupts/IDT.h"
#include "Framebuffer/framebuffer.h"
#include "Framebuffer/kPrintf.h"
#include "Memory/physicalMemory.h"

#include <stdint.h>

#include "Interrupts/interrupts.h"

extern void exception();

void kernel_entry(KernelBootData* bootData)
{
	framebuffer_init((uint32_t*)bootData->framebufferAddress, bootData->framebufferWidth, bootData->framebufferHeight,
					 bootData->framebufferPixelsPerRow, FRAMEBUFFER_BLACK, FRAMEBUFFER_WHITE);

	framebuffer_clear();
	
	gdt_init();

	idt_init();

	physical_mem_init(bootData->entries, bootData->memoryEntryCount);
}