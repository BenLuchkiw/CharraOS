#pragma once

#include "../kernel.h"

#include <stddef.h>
#include <stdbool.h>

void physical_mem_init(KernelBootMemoryEntry* entries, uint8_t entryCount);

// Num is 4KiB pages
void* physical_mem_alloc(size_t num);
void physcial_mem_free(void* pAddr, size_t num);