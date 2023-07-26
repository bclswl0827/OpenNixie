#ifndef __FRAMEWORK_WIRE__H
#define __FRAMEWORK_WIRE__H

#ifndef __SDCC
#error "This header file must be used for SDCC compiler !"
#endif

#include <stdint.h>

#include "config.h"
#include "framework/delay.h"

#define PIN_WIRE_SDA P20  // SDA 引脚
#define PIN_WIRE_SCL P21  // SCL 引脚

#define I2C_START 1   // 开始传输
#define I2C_RESUME 0  // 连续传输

void WireBegin(void);
void WireWrite(uint8_t dat);
void WireBeginTransmission(uint8_t addr);
uint8_t WireRead(void);
uint8_t WireEndTransmission(void);
uint8_t WireRequestFrom(uint8_t addr, uint8_t len);

#endif
