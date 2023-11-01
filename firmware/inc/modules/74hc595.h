#ifndef __MODULE_74HC595_H
#define __MODULE_74HC595_H

#ifndef __SDCC
#error "This header file must be used for SDCC compiler !"
#endif

#include <reg52.h>
#include <stdint.h>

#define LATCH P24
#define DATA P23
#define CLOCK P22

#define ON 1
#define OFF 0

void shiftOut(uint16_t val);
uint8_t setBit(uint8_t val);
uint8_t setSymbol(uint8_t val);
uint8_t setEnable(uint8_t val);
uint16_t setSegment(uint8_t val);
uint16_t setNixie(uint8_t enable,
                  uint8_t symbol,
                  uint8_t _bit,
                  uint16_t segment);

#endif
