#include "framework/stream.h"

uint16_t _stream_timeout = 10000;

// 初始化串口
void SerialBegin(uint16_t b) {
    TMOD = 0x20;
    SCON = 0x50;
    TH1 = 256 - FOSC / 16 / 12 / b;
    TL1 = TH1;
    PCON = 0x80;
    TR1 = 0x01;
    EA = 0x01;
    ES = 0x01;
}

// 结束串口
void SerialEnd() {
    // 关闭总中断和接收中断
    EA = ES = 0;
}

// 等待串行数据的最大时间，单位毫秒
void SerialSetTimeout(uint16_t t) {
    _stream_timeout = t;
}

// 等待串口数据发送完成
void SerialFlush() {
    // 等待完成
    while (!TI) {
        ;
    }
    // 清除发送完成标志
    TI = 0;
}

// 串口发送单个字符
void SerialWrite(uint8_t c) {
    // 关串口中断
    ES = 0;
    // 发送数据
    SBUF = c;
    // 等待完成
    while (!TI) {
        ;
    }
    // 清除发送成功标志
    TI = 0;
    // 打开串口中断
    ES = !TI;
}

// 串口发送字符串
void SerialPrint(uint8_t* s) {
    // 操作指针
    while (*s) {
        SerialWrite(*s++);
    }
}

// 串口发送带换行符字符串
void SerialPrintln(uint8_t* s) {
    // 字符串发送结束后发送换行符
    SerialPrint(s);
    SerialPrint("\r\n");
}

// 串口读取单个字符
uint8_t SerialRead() {
    // 等待完成
    for (uint16_t i = 0; i < _stream_timeout; i++) {
        if (RI) {
            break;
        }
    }
    // 清除接收成功标志
    RI = 0;
    // 返回接收到的字符
    return SBUF;
}

// 在超时前找到目标
uint8_t SerialFind(uint8_t c) {
    uint16_t t = _stream_timeout;
    while (t--) {
        if (SerialRead() == c) {
            return 1;
        }
    }
    return 0;
}

// 串口读取指定长度字符串
void SerialReadBytes(uint8_t* buf, uint8_t length) __reentrant {
    // 丢弃第一个字符
    SerialRead();
    // 操作 uint8_t 指针
    while (length--) {
        *buf++ = SerialRead();
    }
}

// 判断串口是否有数据
uint8_t SerialAvailable() {
    // 读取接收中断标志
    return RI;
}
