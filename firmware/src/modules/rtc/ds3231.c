#include "modules/rtc/ds3231.h"

// BCD 转整数
uint8_t bcdToDec(uint8_t bcd) {
    return (bcd / 16 * 10) + (bcd % 16);
}

// 整数转 BCD
uint8_t decToBcd(uint8_t dec) {
    return (dec / 10 * 16) + (dec % 10);
}

void rtcInit() {
    WireBegin();
}

// 取得时间
void getTime(time_t* time) {
    WireBeginTransmission(DS3231_ADDRESS);
    WireWrite(0x00);
    WireEndTransmission();
    WireRequestFrom(DS3231_ADDRESS, 7);

    time->second = bcdToDec(WireRead() & 0x7F);
    time->minute = bcdToDec(WireRead());
    time->hour = bcdToDec(WireRead());
    time->week = bcdToDec(WireRead());
    time->day = bcdToDec(WireRead());
    time->month = bcdToDec(WireRead());
    time->year = bcdToDec(WireRead());
}

// 设定时间
void setTime(time_t* time) {
    WireBeginTransmission(DS3231_ADDRESS);
    WireWrite(0x00);

    WireWrite(decToBcd(time->second));
    WireWrite(decToBcd(time->minute));
    WireWrite(decToBcd(time->hour));
    WireWrite(decToBcd(time->week));
    WireWrite(decToBcd(time->day));
    WireWrite(decToBcd(time->month));
    WireWrite(decToBcd(time->year));

    WireEndTransmission();
}
