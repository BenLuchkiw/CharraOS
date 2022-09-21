#include <string.h>

#include <stddef.h>
#include <stdint.h>

#include "../../kernel/Framebuffer/kPrintf.h"

void *memset(void *str, int c, size_t n)
{
    // TODO: a better implementation should be used
    
    char* ptr = (char*)(str);
    for(size_t i = 0; i < n; i++, ptr++)
    {
        *ptr = c;
    }

    return str;
}