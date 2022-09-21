#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct Bitmap
{
    uint8_t* bitmap;
    // size is in bits
    size_t size;

    // Not used internally
    size_t firstFree;
}Bitmap;

void bitmap_set_bit(Bitmap* map, size_t index);
void bitmap_clear_bit(Bitmap* map, size_t index);
void bitmap_set_range(Bitmap* map, size_t startIndex, size_t endIndex);
void bitmap_clear_range(Bitmap* map, size_t startIndex, size_t endIndex);
bool bitmap_get_bit(Bitmap* map, size_t index);

// Val is either 0 or 1
void bitmap_clear(Bitmap* map, bool val);