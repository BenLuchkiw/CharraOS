#pragma once

#include <stdint.h>
#include <stddef.h>

enum KernelMemoryFlags
{
    KERNEL_MEMORY_FLAG_USABLE      = 1,
    KERNEL_MEMORY_FLAG_RECLAIMABLE = 2,
    KERNEL_MEMORY_FLAG_KERNEL      = 3,
    KERNEL_MEMORY_FLAG_RESERVED    = 4
};

enum KernelFramebufferPixelType
{
    KERNEL_FRAMEBUFFER_PIXEL_TYPE_RRGGBBXX,
    KERNEL_FRAMEBUFFER_PIXEL_TYPE_BBGGRRXX,
    KERNEL_FRAMEBUFFER_PIXEL_TYPE_UNKNOWN
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
    uint16_t framebufferPixelsPerRow;
    enum KernelFramebufferPixelType FramebufferType;

    uint8_t memoryEntryCount;
    KernelBootMemoryEntry entries[];
} KernelBootData;

void kernel_entry(KernelBootData* bootData);