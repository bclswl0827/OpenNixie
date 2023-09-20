#include "framework/stream.h"
#include "modules/ds3231.h"
#include "modules/shift.h"

#define CMD_WORD 0xE0
#define ACK_WORD 0xE1

#define YEAR_WORD 0xF1
#define MONTH_WORD 0xF2
#define DAY_WORD 0xF3
#define WEEK_WORD 0xF4
#define HOUR_WORD 0xF5
#define MINUTE_WORD 0xF6
#define SECOND_WORD 0xF7

void setProtection() {
    for (uint8_t i = 0; i < 10; i++) {
        uint16_t s0 = setSegment(i);
        uint16_t s1 = setSegment(i);
        uint16_t s2 = setSegment(i);
        uint16_t s3 = setSegment(i);

        uint8_t enable = setEnable(ON);
        uint8_t symbol = setSymbol(OFF);
        for (uint8_t j = 0; j < 5; j++) {
            shiftOut(setNixie(enable, symbol, setBit(0), s0));
            shiftOut(setNixie(enable, symbol, setBit(1), s1));
            shiftOut(setNixie(enable, symbol, setBit(2), s2));
            shiftOut(setNixie(enable, symbol, setBit(3), s3));

            delayMicroseconds(10);
            shiftOut(setNixie(enable, symbol, setBit(OFF), OFF));
        }
    }
}

void main() {
    time_t time;
    SerialBegin(9600);
    SerialWrite(ACK_WORD);
    uint8_t enable = setEnable(1);

    while (1) {
        for (uint8_t i = 0; i < 4; i++) {
            for (uint16_t j = 0; j < 800; j++) {
                if (SerialAvailable() && SerialRead() == CMD_WORD) {
                    uint8_t cmd = SerialRead();
                    uint8_t dat = SerialRead();

                    switch (cmd) {
                        case YEAR_WORD:
                            time.year = dat;
                            break;
                        case MONTH_WORD:
                            time.month = dat;
                            break;
                        case DAY_WORD:
                            time.day = dat;
                            break;
                        case WEEK_WORD:
                            time.week = dat;
                            break;
                        case HOUR_WORD:
                            time.hour = dat;
                            break;
                        case MINUTE_WORD:
                            time.minute = dat;
                            break;
                        case SECOND_WORD:
                            time.second = dat;
                            break;
                    }

                    setTime(&time);
                    SerialWrite(ACK_WORD);
                }

                getTime(&time);
                uint16_t seg0 = 0;
                uint16_t seg1 = 0;
                uint16_t seg2 = 0;
                uint16_t seg3 = 0;
                uint8_t symbol = setSymbol(ON);

                switch (j / 200) {
                    case 0:
                        seg0 = setSegment(time.hour / 10);
                        seg1 = setSegment(time.hour % 10);
                        seg2 = setSegment(time.minute / 10);
                        seg3 = setSegment(time.minute % 10);
                        break;
                    case 1:
                        seg0 = setSegment(time.minute / 10);
                        seg1 = setSegment(time.minute % 10);
                        seg2 = setSegment(time.second / 10);
                        seg3 = setSegment(time.second % 10);
                        break;
                    case 2:
                        seg0 = setSegment(time.month / 10);
                        seg1 = setSegment(time.month % 10);
                        seg2 = setSegment(time.day / 10);
                        seg3 = setSegment(time.day % 10);
                        symbol = setSymbol(OFF);
                        break;
                    case 3:
                        seg0 = setSegment(2);
                        seg1 = setSegment(0);
                        seg2 = setSegment(time.year / 10);
                        seg3 = setSegment(time.year % 10);
                        symbol = setSymbol(OFF);
                        break;
                }

                shiftOut(setNixie(enable, symbol, setBit(0), seg0));
                shiftOut(setNixie(enable, symbol, setBit(1), seg1));
                shiftOut(setNixie(enable, symbol, setBit(2), seg2));
                shiftOut(setNixie(enable, symbol, setBit(3), seg3));

                delayMicroseconds(10);
                shiftOut(setNixie(enable, symbol, OFF, OFF));
            }

            if (i == 3) {
                setProtection();
            }
        }
    }
}
