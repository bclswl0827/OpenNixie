#ifndef __MODULE_RTC_DS3231_H
#define __MODULE_RTC_DS3231_H

#ifndef __SDCC
#error "This header file must be used for SDCC compiler !"
#endif

#include <stdint.h>
#include <wire.h>

#include "modules/rtc/types.h"

void getTime(time_t* time);
void setTime(time_t* time);

#endif
