#pragma once

#include <Wire.h>
#include <stdint.h>
#include <uRTCLib.h>

class Time {
   private:
    uRTCLib* rtc;

   public:
    struct TimeData {
        uint_least8_t year;
        uint_least8_t month;
        uint_least8_t day;
        uint_least8_t week;
        uint_least8_t hour;
        uint_least8_t minute;
        uint_least8_t second;
    };
    TimeData timeData;

    Time(uint_least8_t sdaPin,
         uint_least8_t sclPin,
         uint_least8_t slaveAddr,
         uint_least8_t model);
    Time::TimeData getTime();
    void setTime(uint_least8_t year,
                 uint_least8_t month,
                 uint_least8_t day,
                 uint_least8_t hour,
                 uint_least8_t minute,
                 uint_least8_t second,
                 uint_least8_t week);
};
