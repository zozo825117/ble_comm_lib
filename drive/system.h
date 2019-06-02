#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "GW32L.h"

void system_init(void);
void wdt_init(void);
void system_tdma(void);
void ResetNoReadOption(void);
void Timer2_init(void);
//void ResetReadOption(void);

#endif


