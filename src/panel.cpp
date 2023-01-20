#include <panel.hpp>

Panel::Panel(uint_least8_t timePin,
             uint_least8_t redPin,
             uint_least8_t greenPin,
             uint_least8_t bluePin) {
    // 初始化引脚
    pinMode(timePin, INPUT_PULLUP);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    // 初始化变量
    this->timePin = timePin;
    this->redPin = redPin;
    this->greenPin = greenPin;
    this->bluePin = bluePin;
}

// 设定指示灯颜色
void Panel::setColor(uint_least8_t redVal,
                     uint_least8_t greenVal,
                     uint_least8_t blueVal) {
    currentColor = (redVal << 2) | (greenVal << 1) | blueVal;
    digitalWrite(redPin, redVal);
    digitalWrite(greenPin, greenVal);
    digitalWrite(bluePin, blueVal);
}
