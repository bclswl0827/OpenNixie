#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <stdint.h>

class Blueth {
   private:
    SoftwareSerial* Serial;
    uint_least8_t firstRead = 1;

   public:
    Blueth(uint_least8_t rxPin, uint_least8_t txPin, uint_least16_t baudRate);
    uint_least8_t getMessage(uint_least8_t buffer[20],
                             uint_least16_t timeout,
                             uint_least8_t retry,
                             uint_least8_t minute,
                             uint_least8_t second);
    void setMessage(uint_least8_t msg);
};
