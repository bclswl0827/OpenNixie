#ifndef __FRAMEWORK_STREAM__H
#define __FRAMEWORK_STREAM__H

#ifndef __SDCC
#error "This header file must be used for SDCC compiler !"
#endif

#ifdef USE_STDIO
#include <stdio.h>
#endif

#include <reg52.h>
#include <stdint.h>

#include "config.h"

void SerialBegin(uint16_t b);
void SerialEnd();
void SerialSetTimeout(uint16_t t);
void SerialFlush();
void SerialWrite(uint8_t c);
void SerialPrint(uint8_t* s);
void SerialPrintln(uint8_t* s);
uint8_t SerialRead();
uint8_t SerialFind(uint8_t c);
void SerialReadBytes(uint8_t* buf, uint8_t length) __reentrant;
uint8_t SerialAvailable();
#ifdef USE_STDIO
int putchar(uint8_t c);
#endif

#endif
