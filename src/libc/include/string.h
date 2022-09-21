#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dest, const void * src, size_t n);
void *memset(void *str, int c, size_t n);

#ifdef __cplusplus
}
#endif