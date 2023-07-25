#include "framework/delay.h"

// 延时函数，单位 ms，不精确，慎用
void delay(uint16_t t) {
    // 内层循环次数
    uint_least8_t count = 70;
    // 短延时下改变内层循环次数
    if (t < 20) {
        count = 47;
    } else if (t < 10) {
        count = 1;
        t /= 2;
    }
    for (uint16_t i = 0; i < t; i++) {
        for (uint16_t j = 0; j < count; j++) {
            ;
        }
    }
}

// 延时函数，单位 us，不精确，慎用
void delayMicroseconds(uint16_t t) {
    // t 减到 0
    while (--t) {
        ;
    }
}
