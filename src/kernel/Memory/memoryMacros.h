#pragma once

#define ALIGN_UP(address, alignVal)   ((address) & ~((alignVal)-1))
#define ALIGN_DOWN(address, alignVal) (((address) + (alignVal)-1) & ~((alignVal)-1))

#define KERNEL_PHYS_TO_VIRT_ADDR(address, base) (address + base)