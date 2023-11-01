#ifndef __51DUINO_CONFIG__H
#define __51DUINO_CONFIG__H

#ifndef __SDCC
#error "This header file must be used for SDCC compiler !"
#endif

#include <reg52.h>

// 设定晶振频率，以 Hz 为单位
#define FOSC 11059200L

// 电平值定义
#define LOW 0   // 低电平
#define HIGH 1  // 高电平

#endif
