#pragma once

#include <Arduino.h>
#include <stdint.h>

class Utils {
   public:
    uint_least8_t getTens(uint_least8_t num);
    uint_least8_t getUnits(uint_least8_t num);
    uint_least8_t getNum(uint_least8_t ch);
    uint_least8_t getSum(uint_least8_t part_1, uint_least8_t part_2);
};