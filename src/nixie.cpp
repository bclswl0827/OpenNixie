#include <nixie.hpp>

Nixie::Nixie(uint_least8_t latchPin,
             uint_least8_t dataPin,
             uint_least8_t clockPin) {
    // 初始化引脚
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    // 初始化变量
    this->latchPin = latchPin;
    this->dataPin = dataPin;
    this->clockPin = clockPin;
}

// 计算移位寄存器 4 位输出值
uint_least8_t Nixie::getShift(uint_least8_t num) {
    switch (num) {
        case 0:
            return 0x00;
        case 1:
            return 0x08;
        case 2:
            return 0x04;
        case 3:
            return 0x0C;
        case 4:
            return 0x02;
        case 5:
            return 0x0A;
        case 6:
            return 0x06;
        case 7:
            return 0x0E;
        case 8:
            return 0x01;
        case 9:
            return 0x09;
        default:
            return 0x0F;
    }
}

// 设定辉光管 X（4-7 脚、阳极、电平反转）/ Y（0-3 脚阴极）轴之值
void Nixie::setShift(uint_least8_t segment_1,
                     uint_least8_t segment_2,
                     uint_least8_t segment_3,
                     uint_least8_t segment_4,
                     uint_least16_t t) {
    uint_least8_t val = 0;
    uint_least64_t start = millis();
    while (millis() - start <= t) {
        val = (getShift(segment_1) << 4) | 0x07;
        shiftOut(latchPin, dataPin, clockPin, val);
        delay(12);
        val = (getShift(segment_1) << 4) | 0x0B;
        shiftOut(latchPin, dataPin, clockPin, val);
        delay(12);
        val = (getShift(segment_1) << 4) | 0x0D;
        shiftOut(latchPin, dataPin, clockPin, val);
        delay(12);
        val = (getShift(segment_1) << 4) | 0x0E;
        shiftOut(latchPin, dataPin, clockPin, val);
        delay(12);
    }
}

// 简化的 shiftOut 函数
void Nixie::shiftOut(uint_least8_t latchPin,
                     uint_least8_t dataPin,
                     uint_least8_t clockPin,
                     uint_least16_t val) {
    for (uint_least8_t i = 0; i < 8; i++) {
        digitalWrite(latchPin, LOW);
        digitalWrite(dataPin, !!(val & (1 << i)));
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
        digitalWrite(latchPin, HIGH);
    }
}

// 阴极保护函数
void Nixie::setProtect(uint_least8_t loop, uint_least16_t interval) {
    for (uint_least8_t i = 0; i < loop; i++) {
        for (uint_least8_t j = 0; j < 10; j++) {
            setShift(j, j, j, j, interval);
        }
    }
}