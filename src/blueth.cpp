#include <blueth.hpp>

Blueth::Blueth(uint_least8_t rxPin,
               uint_least8_t txPin,
               uint_least16_t baudRate) {
    this->Serial = new SoftwareSerial(rxPin, txPin);
    this->Serial->begin(baudRate);
}

// 取得时间数据
uint_least8_t Blueth::getMessage(uint_least8_t buffer[20],
                                 uint_least16_t timeout,
                                 uint_least8_t retry,
                                 uint_least8_t minute,
                                 uint_least8_t second) {
    // 设定超时时间
    Serial->setTimeout(timeout);
    // 报文以 $ 开头，* 结尾
    if (Serial->available() && Serial->find('$') && retry) {
        // 读取 20 个字节
        Serial->readBytes(buffer, 20);
        // 若报文为心跳，则回应心跳后重试
        if (buffer[1] == 'P' && buffer[2] == 'I' && buffer[3] == 'N' &&
            buffer[4] == 'G' && buffer[5] == '*') {
            setMessage(0);
            delay(200);
            return getMessage(buffer, timeout, retry, minute, second);
        }
        // 非首次读取，远程时间减本地时间差值为负时则重试
        if (!firstRead &&
            ((10 * (buffer[12] - '0') + (buffer[13] - '0')) - minute < 0 ||
             (10 * (buffer[15] - '0') + (buffer[16] - '0')) - second < 0)) {
            delay(200);
            return getMessage(buffer, timeout, --retry, minute, second);
        }
        // 首次读取、符号位错误、出现异常字符则重试
        if (buffer[18] == '0' || buffer[18] == '8' || buffer[18] == '9' ||
            buffer[19] != '*' || buffer[2] != buffer[5] || firstRead ||
            buffer[8] != buffer[11] || buffer[14] != buffer[17]) {
            if (firstRead) {
                firstRead = 0;
            }
            delay(200);
            return getMessage(buffer, timeout, --retry, minute, second);
        }
        // 通告对时完成
        setMessage(2);
        return 1;
    }
    return 0;
}

// 发送上位机指令
void Blueth::setMessage(uint_least8_t msg) {
    // 报文以 $ 开头，* 结尾
    switch (msg) {
        // 心跳回应
        case 0:
            Serial->println("$PONG*");
            break;
        // 对时请求
        case 1:
            Serial->println("$GET*");
            break;
        // 对时完成
        case 2:
            Serial->println("$DONE*");
            break;
        default:
            break;
    }
}