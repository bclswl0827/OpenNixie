#pragma once

#include <Arduino.h>
#include <stdint.h>

class Panel {
   private:
    uint_least8_t timePin, redPin, greenPin, bluePin;

   public:
    uint_least8_t currentColor;
    uint_least16_t lastClick;

    Panel(uint_least8_t timePin,
          uint_least8_t redPin,
          uint_least8_t greenPin,
          uint_least8_t bluePin);
    void setColor(uint_least8_t redVal,
                  uint_least8_t greenVal,
                  uint_least8_t blueVal);
};
