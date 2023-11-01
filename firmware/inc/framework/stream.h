#ifndef __FRAMEWORK_STREAM__H
#define __FRAMEWORK_STREAM__H

#ifndef __SDCC
#error "This header file must be used for SDCC compiler !"
#endif

#include "config.h"

#ifdef USE_STDIO
#include <stdio.h>
#endif

#include <reg52.h>
#include <stdint.h>

void SerialBegin(uint16_t b);
void SerialEnd(void);
void SerialSetTimeout(uint16_t t);
void SerialFlush(void);
void SerialWrite(uint8_t c);
void SerialPrint(uint8_t* s);
void SerialPrintln(uint8_t* s);
uint8_t SerialRead(void);
uint8_t SerialFind(uint8_t c);
void SerialReadBytes(uint8_t* buf, uint8_t length) __reentrant;
uint8_t SerialAvailable(void);

#endif
