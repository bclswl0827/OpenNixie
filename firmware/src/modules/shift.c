#include "modules/shift.h"

uint16_t setSegment(uint8_t val) {
    return val < 10 ? 1 << val : 0;
}

uint8_t setBit(uint8_t val) {
    switch (val) {
        case 3:
            return 0x07;
        case 2:
            return 0x0B;
        case 1:
            return 0x0D;
        case 0:
            return 0x0E;
    }

    return 0x0F;
}

uint8_t setSymbol(uint8_t val) {
    return val ? 1 : 0;
}

uint8_t setEnable(uint8_t val) {
    return val ? 0 : 1;
}

uint16_t setNixie(uint8_t enable,
                  uint8_t symbol,
                  uint8_t _bit,
                  uint16_t segment) {
    return (enable << 15) | (symbol << 14) | (_bit << 10) | segment;
}

void shiftOut(uint16_t val) {
    LATCH = 0;

    for (uint8_t i = 0; i < 16; i++) {
        DATA = !!(val & (1 << (15 - i)));
        CLOCK = 1;
        CLOCK = 0;
    }

    LATCH = 1;
}
