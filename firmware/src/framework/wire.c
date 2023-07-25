#include "framework/wire.h"

#define I2C_START 1   // 开始传输
#define I2C_RESUME 0  // 连续传输

uint8_t _wire_address = 0x00,  // 全局变量记录地址
    _wire_status = I2C_START,  // 继续传输标志
    _wire_remain = 0;          // 剩余字节数

// 初始化 I2C 总线
void WireBegin() {
    PIN_WIRE_SDA = LOW;
    PIN_WIRE_SCL = LOW;
}

// 启动 I2C 传输
void WireBeginTransmission(uint8_t addr) {
    _wire_address = addr;
    // 发出启动信号
    PIN_WIRE_SDA = HIGH;
    PIN_WIRE_SCL = HIGH;
    PIN_WIRE_SDA = LOW;
    PIN_WIRE_SCL = LOW;
    // 发送设备地址
    WireWrite(addr << 1);
}

// 结束 I2C 传输
uint8_t WireEndTransmission() {
    PIN_WIRE_SDA = LOW;
    PIN_WIRE_SCL = HIGH;
    PIN_WIRE_SDA = HIGH;
    return 1;
}

// I2C 读取 1 字节
uint8_t WireRead() {
    uint8_t dat = 0;

    if (_wire_status == I2C_START) {
        // 进入接收模式
        PIN_WIRE_SDA = HIGH;
        PIN_WIRE_SCL = HIGH;
        PIN_WIRE_SDA = LOW;
        PIN_WIRE_SCL = LOW;
        // 送出读地址
        WireWrite((_wire_address << 1) | 1);
    }

    // 剩余字节为 0 时进入重置状态
    if (!--_wire_remain) {
        _wire_status = I2C_START;
    }

    // 循环 8 次将一个字节读出，先读高再传低位
    PIN_WIRE_SDA = HIGH;
    for (uint8_t i = 0; i < 8; i++) {
        dat <<= 1;
        PIN_WIRE_SCL = HIGH;
        dat |= PIN_WIRE_SDA;
        PIN_WIRE_SCL = LOW;
    }

    // 存在剩余字节则发送 ACK，否则为 NACK
    PIN_WIRE_SDA = _wire_remain ? LOW : HIGH;
    PIN_WIRE_SCL = HIGH;
    PIN_WIRE_SCL = LOW;

    return dat;
}

// I2C 发送 1 字节
void WireWrite(uint8_t dat) {
    // 循环 8 次将一个字节传出，先传高位再传低位
    PIN_WIRE_SCL = LOW;
    for (uint8_t i = 0; i < 8; i++) {
        PIN_WIRE_SDA = dat & 0x80;
        dat <<= 1;
        PIN_WIRE_SCL = HIGH;
        PIN_WIRE_SCL = LOW;
    }

    PIN_WIRE_SCL = HIGH;
    delayMicroseconds(5);
    PIN_WIRE_SCL = LOW;
}

// 从指定地址读取指定长度的数据
uint8_t WireRequestFrom(uint8_t addr, uint8_t len) {
    if (len < 2) {
        return 0;
    }

    // 进入接收模式
    PIN_WIRE_SDA = HIGH;
    PIN_WIRE_SCL = HIGH;
    PIN_WIRE_SDA = LOW;
    PIN_WIRE_SCL = LOW;
    // 送出读地址
    WireWrite((_wire_address << 1) | 1);

    _wire_address = addr;
    _wire_remain = len;
    _wire_status = I2C_RESUME;

    return len;
}
