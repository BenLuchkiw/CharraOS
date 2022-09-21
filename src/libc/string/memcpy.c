#include <string.h>

void *memcpy(void *dest, const void * src, size_t n)
{
    // TODO: make this better
    
    char* srcChar = (char*)src;
    char* destChar = (char*)dest;
    // make sure src is 8 byte aligned
    uint64_t offset = (uint64_t)src % 8;
    n -= offset;

    for(; offset != 0; offset--, srcChar++, destChar++)
    {
        *destChar = *srcChar;
    }

    int iterations = n / 64;
    uint64_t* src64 = (uint64_t*)srcChar;
    uint64_t* dest64 = (uint64_t*)destChar;
    for(; iterations != 0; iterations--, n--, src64++, dest64++)
    {
        *dest64 = *src64;
    }

    srcChar = (char*)src64;
    destChar = (char*)dest64;
    for(;n != 0; n++, srcChar++, destChar++)
    {
        *destChar = *srcChar;
    }

    uint64_t srcEnd = (uint64_t)src + (n * 8);
    srcEnd = srcEnd - ((n * 8) % 64);

    return dest;
}