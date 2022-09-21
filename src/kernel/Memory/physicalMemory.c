#include "physicalMemory.h"

#include "../Framebuffer/kPrintf.h"
#include "bitmap.h"
#include "memoryMacros.h"

#include <stdint.h>
#include <string.h>

static Bitmap map;

void physical_mem_init(KernelBootMemoryEntry* entries, uint8_t entryCount)
{

}

void* physical_mem_alloc(size_t num)
{
	void* result = NULL;
	if(num == 1)
	{
		result = (void*)(map.firstFree * 4096);
		bitmap_set_bit(&map, map.firstFree);
	}
	else
	{
		bool found = false;
		for(size_t i = map.firstFree; i < map.size; i++)
		{
			for(size_t x = 0; x < num; x++)
			{
				if(bitmap_get_bit(&map, i + x))
				{
					x += i;
					break;
				}
				// If the row has been found set all bits and set address
				if(x == (num - 1))
				{
					for(size_t x = 0; x < num; x++)
					{
						bitmap_set_bit(&map, i + x);
					}
					result = (void*)(i * 4096);
					found = true;
					map.firstFree = i;

					break;
				}
			}
			if(found)
			{
				break;
			}
		}
	}

	// Find the next free bit for map.firstFree
	for(size_t i = map.firstFree; i < map.size; i++)
	{
		if(!bitmap_get_bit(&map, i))
		{
			map.firstFree = i;
			break;
		}
	}

	return result;
}

void physcial_mem_free(void* pAddr, size_t num)
{
	uint64_t bitmapIndex = (uint64_t)pAddr / 4096;
	for(size_t i = bitmapIndex; i < bitmapIndex + num; i++)
	{
		bitmap_clear_bit(&map, i);
	}

	if(bitmapIndex < map.firstFree)
	{
		map.firstFree = bitmapIndex;
	}
}