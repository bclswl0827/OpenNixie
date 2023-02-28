#pragma once

#include <Arduino.h>
#include <stdint.h>

class Nixie {
   private:
    uint_least8_t latchPin, dataPin, clockPin;

    uint_least8_t getShift(uint_least8_t num);
    void shiftOut(uint_least8_t latchPin,
                  uint_least8_t dataPin,
                  uint_least8_t clockPin,
                  uint_least16_t val);

   public:
    Nixie(uint_least8_t latchPin,
          uint_least8_t dataPin,
          uint_least8_t clockPin);
    void setShift(uint_least8_t segment_0,
                  uint_least8_t segment_1,
                  uint_least8_t segment_2,
                  uint_least8_t segment_3,
                  uint_least8_t scan_speed,
                  uint_least16_t scan_time);
    void setProtect(uint_least16_t scan_time);
};
