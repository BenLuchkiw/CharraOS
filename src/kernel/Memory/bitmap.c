#include "bitmap.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void bitmap_set_bit(Bitmap* map, size_t index)
{
	uint8_t mask = 1 << (index % 8);

	index /= 8;

	map->bitmap[index] |= mask;
}

void bitmap_clear_bit(Bitmap* map, size_t index)
{
	uint8_t mask = 1 << (index % 8);
	mask = !mask;

	index /= 8;

	map->bitmap[index] &= mask;
}

void bitmap_set_range(Bitmap* map, size_t startIndex, size_t endIndex)
{
	// Bits that cannot be assigned with memset
	int preAlignedBits = 8 - (startIndex % 8);
	int postAlignedBits = endIndex % 8;
	int size = (endIndex - startIndex) - preAlignedBits - postAlignedBits;

	for(int i = startIndex; preAlignedBits != 0; preAlignedBits--, i++)
	{
		bitmap_set_bit(map, i);
	}

	for(int i = endIndex - postAlignedBits; postAlignedBits != 0; postAlignedBits--, i++)
	{
		bitmap_set_bit(map, i);
	}

	uint8_t* address = (uint8_t*)(map->bitmap) + (startIndex + preAlignedBits);

	memset(address, 1, size);
}

void bitmap_clear_range(Bitmap* map, size_t startIndex, size_t endIndex)
{
	// Bits that cannot be assigned with memset
	int preAlignedBits = 8 - (startIndex % 8);
	int postAlignedBits = endIndex % 8;
	int size = (endIndex - startIndex) - preAlignedBits - postAlignedBits;

	for(int i = startIndex; preAlignedBits != 0; preAlignedBits--, i++)
	{
		bitmap_clear_bit(map, i);
	}

	for(int i = endIndex - postAlignedBits; postAlignedBits != 0; postAlignedBits--, i++)
	{
		bitmap_clear_bit(map, i);
	}

	uint8_t* address = (uint8_t*)(map->bitmap) + (startIndex + preAlignedBits);

	memset(address, 0, size);
}

bool bitmap_get_bit(Bitmap* map, size_t index)
{
	uint8_t mask = 1 << (index % 8);

	index /= 8;

	return map->bitmap[index] & mask;
}

void bitmap_clear(Bitmap* map, bool val)
{
	memset(map->bitmap, val, map->size / 8);
}