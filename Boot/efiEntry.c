#include "efi.h"

#include <stdbool.h>

#include <kernel/kernel.h>

/*
enum KernelMemoryFlags
{
    KERNEL_MEMORY_FLAG_USABLE      = 1,
    KERNEL_MEMORY_FLAG_RECLAIMABLE = 2,
    KERNEL_MEMORY_FLAG_KERNEL      = 3,
    KERNEL_MEMORY_FLAG_RESERVED    = 4
};

typedef struct 
{
    uint8_t memoryType;
    uint64_t baseAddress;
    uint64_t Length;
} KernelBootMemoryEntry;

typedef struct 
{
    uint64_t framebufferAddress;
    uint16_t framebufferWidth;
    uint16_t framebufferHeight;
    uint16_t framebufferBytesPerRow;

    uint8_t memoryEntryCount;
    KernelBootMemoryEntry entries[];
} KernelBootData;
*/

EFI_STATUS efi_main(EFI_HANDLE imageHandle, EFI_SYSTEM_TABLE* systemTable)
{
	(void)imageHandle;
	EFI_STATUS status;
	EFI_INPUT_KEY key;

	// Collect all information from system table

	EFI_GRAPHICS_OUTPUT_PROTOCOL* GOP = NULL;
	EFI_GUID GOPGUID = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	status = systemTable->BootServices->LocateProtocol(&GOPGUID, NULL, (void**)GOP);
	if(EFI_ERROR(status))
		return status;

	// Load CharraOS.elf
		

	// Get memory map

	// Package all data for the kernel
	KernelBootData kernelData;
	kernelData.framebufferAddress = GOP->Mode->FrameBufferBase;
	kernelData.framebufferWidth = GOP->Mode->Info->HorizontalResolution;
	kernelData.framebufferHeight = GOP->Mode->Info->VerticalResolution;
	kernelData.framebufferPixelsPerRow = GOP->Mode->Info->PixelsPerScanLine;
	if(GOP->Mode->Info->PixelFormat == PixelRedGreenBlueReserved8BitPerColor)
	{
		kernelData.FramebufferType = KERNEL_FRAMEBUFFER_PIXEL_TYPE_RRGGBBXX;
	}
	else if(GOP->Mode->Info->PixelFormat == PixelBlueGreenRedReserved8BitPerColor)
	{
		kernelData.FramebufferType = KERNEL_FRAMEBUFFER_PIXEL_TYPE_BBGGRRXX;
	}
	else
	{
		kernelData.FramebufferType = KERNEL_FRAMEBUFFER_PIXEL_TYPE_UNKNOWN;
	}

	// Exit boot services and launch kernel
 
	return status;
}