#include <time.hpp>

Time::Time(uint_least8_t sdaPin,
           uint_least8_t sclPin,
           uint_least8_t slaveAddr,
           uint_least8_t model) {
    // 初始化时钟模块
    this->rtc = new uRTCLib(slaveAddr);
    this->rtc->set_model(model);
#ifdef ARDUINO_ARCH_ESP8266
    Wire.begin(sdaPin, sclPin);
#else
    Wire.begin();
#endif
}

// 从模块取得时间并传回 TimeData
Time::TimeData Time::getTime() {
    this->rtc->refresh();
    timeData.year = this->rtc->year();
    timeData.month = this->rtc->month();
    timeData.day = this->rtc->day();
    timeData.hour = this->rtc->hour();
    timeData.minute = this->rtc->minute();
    timeData.second = this->rtc->second();
    timeData.week = this->rtc->dayOfWeek();
    return timeData;
}

// 设置时间并保存到时间模块
void Time::setTime(uint_least8_t year,
                   uint_least8_t month,
                   uint_least8_t day,
                   uint_least8_t hour,
                   uint_least8_t minute,
                   uint_least8_t second,
                   uint_least8_t week) {
    // 时间直接写入模块
    this->rtc->set(second, minute, hour, week, day, month, year);
}
