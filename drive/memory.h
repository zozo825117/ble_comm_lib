#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "GW32L.h"

void memory_init(void);
void *memory_malloc(u8 len);
u8 memory_free(void *ptr,u8 len);

#endif


