#pragma once

// 调试模式开关
#define DEBUG_FLAG 0
// 调试模式波特率
#define DEBUG_BAUD 9600

// 画面切换间隔
#define SWITCH_INTERVAL 5000
// 按钮防抖动时间
#define DEBOUNCE_DELAY 1000
// 对时按钮，须 D2 或 D3
#define TIME_PIN D2

// RTC 模块型号
#define RTC_MODEL 2
// RTC 模块地址
#define RTC_ADDR 0x68
// RTC 模块 SDA
#define RTC_SDA SDA  // PIN_A4
// RTC 模块 SCL
#define RTC_SCL SCL  // PIN_A5

// 蓝牙串口波特率
#define BLUETH_BAUD 9600
// 蓝牙超时时间
#define BLUETH_TIMEOUT 500
// 对时重试次数
#define BLUETH_RETRY 100
// 蓝牙串口 RX
#define BLUETH_RX A2
// 蓝牙串口 TX
#define BLUETH_TX A3

// 红色指示灯
#define LED_RED D7
// 绿色指示灯
#define LED_GREEN D8
// 蓝色指示灯
#define LED_BLUE D9

// 移位寄存器 ST_CP（Latch）
#define LATCH_PIN D10
// 移位寄存器 DS（Data）
#define DATA_PIN D11
// 移位寄存器 SH_CP（Clock）
#define CLOCK_PIN D12