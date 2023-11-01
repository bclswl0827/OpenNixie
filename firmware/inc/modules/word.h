#ifndef __MODULE_WORD_H
#define __MODULE_WORD_H

#ifndef __SDCC
#error "This header file must be used for SDCC compiler !"
#endif

#define CMD_WORD 0xE0
#define ACK_WORD 0xE1

#define YEAR_WORD 0xF1
#define MONTH_WORD 0xF2
#define DAY_WORD 0xF3
#define WEEK_WORD 0xF4
#define HOUR_WORD 0xF5
#define MINUTE_WORD 0xF6
#define SECOND_WORD 0xF7

#endif
