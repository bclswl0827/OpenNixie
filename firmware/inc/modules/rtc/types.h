#ifndef __MODULE_RTC_TYPES_H
#define __MODULE_RTC_TYPES_H

#ifndef __SDCC
#error "This header file must be used for SDCC compiler !"
#endif

#include <stdint.h>

#define DS3231_ADDRESS 0x68

typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t week;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} time_t;

#endif
