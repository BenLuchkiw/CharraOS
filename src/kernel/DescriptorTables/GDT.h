#pragma once

#include <stdint.h>

void gdt_init();

typedef struct GDTSegmentSelector
{
    uint8_t ringLevel : 2;
    uint8_t tableType : 1; // 1 is LDT 0 is GDT
    uint16_t index : 13;
} GDTSegmentSelector;