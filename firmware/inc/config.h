#ifndef __51DUINO_CONFIG__H
#define __51DUINO_CONFIG__H

#ifndef __SDCC
#error "This header file must be used for SDCC compiler !"
#endif

#include <reg52.h>

// 使用标准输入输出
// #define USE_STDIO

// 设定晶振频率，以 Hz 为单位
#define CRYSTAL 11059200L
// 1 个时钟周期为 12 个机器周期
#define CYCLE (CRYSTAL / 12)

// 电平值定义
#define LOW 0   // 低电平
#define HIGH 1  // 高电平

#endif
