#include <blueth.hpp>
#include <config.hpp>
#include <nixie.hpp>
#include <panel.hpp>
#include <time.hpp>
#include <utils.hpp>

// 创建时间模块对象
Time time(RTC_SDA, RTC_SCL, RTC_ADDR, RTC_MODEL);
// 创建辉光管对象
Nixie nixie(SR_LATCH, SR_DATA, SR_CLOCK);
// 创建面板对象
Panel panel(TIME_PIN, RGB_RED, RGB_GRN, RGB_BLE);
// 创建蓝牙对象
Blueth blueth(BLUETH_RX, BLUETH_TX, BLUETH_BAUD);
// 创建工具对象
Utils utils;

// 对时 Flag，在中断中变更
uint_least8_t alignTimeFlag = 0;

// 对时中断函数
void timePinInterrupt() {
    if (millis() - panel.lastClick > DEBOUNCE_DELAY) {
        // 记录当前时刻
        panel.lastClick = millis();
        // 点亮所有面板灯
        panel.setColor(HIGH, HIGH, HIGH);
        // 将对时 Flag 设定为 1
        alignTimeFlag = 1;
    }
}

// 时间校准函数
void alignTime(uint_least8_t flag) {
    if (!flag) {
        return;
    }
#if DEBUG_FLAG == 1
    Serial.println("执行对时程序");
#endif
    // 重置对时 Flag 为 0
    alignTimeFlag = 0;
    // 发送对时指令
    blueth.setMessage(1);
    // 取得当前时间
    time.getTime();
    // 解析时间数据
    uint_least8_t buf[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (blueth.getMessage(buf, BLUETH_TIMEOUT, BLUETH_RETRY,
                          time.timeData.minute, time.timeData.second)) {
        // 保存时间到模块
        time.setTime(utils.getSum(buf[0], buf[1]), utils.getSum(buf[3], buf[4]),
                     utils.getSum(buf[6], buf[7]),
                     utils.getSum(buf[9], buf[10]),
                     utils.getSum(buf[12], buf[13]),
                     utils.getSum(buf[15], buf[16]), utils.getNum(buf[18]));
        // 点亮绿色面板灯
        panel.setColor(LOW, HIGH, LOW);
#if DEBUG_FLAG == 1
        for (uint_least8_t i = 0; i < 20; i++) {
            Serial.write(buf[i]);
        }
        Serial.println("\r\n时间数据解析成功");
#endif
    } else {
        // 解析失败亮红灯
        panel.setColor(HIGH, LOW, LOW);
#if DEBUG_FLAG == 1
        for (uint_least8_t i = 0; i < 20; i++) {
            Serial.write(buf[i]);
        }
        Serial.println("\r\n时间数据解析失败");
#endif
    }
}

void setup() {
    // 初始化中断服务
    attachInterrupt(digitalPinToInterrupt(TIME_PIN), timePinInterrupt, FALLING);
    // 点亮蓝色面板灯
    panel.setColor(LOW, LOW, HIGH);
    // 初始化串口
#if DEBUG_FLAG == 1
    Serial.begin(DEBUG_BAUD);
    Serial.println("串口已经打开");
#endif
}

void loop() {
    // 串口显示时间
#if DEBUG_FLAG == 1
    time.getTime();
    Serial.print(time.timeData.year + 2000);
    Serial.print("/");
    Serial.print(time.timeData.month);
    Serial.print("/");
    Serial.print(time.timeData.day);
    Serial.print(" ");
    Serial.print(time.timeData.hour);
    Serial.print(":");
    Serial.print(time.timeData.minute);
    Serial.print(":");
    Serial.println(time.timeData.second);
#endif
    // 显示时间
#if DEBUG_FLAG == 1
    Serial.println("显示当前时间");
#endif
    time.getTime();
    nixie.setShift(utils.getTens(time.timeData.hour),
                   utils.getUnits(time.timeData.hour),
                   utils.getTens(time.timeData.minute),
                   utils.getUnits(time.timeData.minute), SCAN_SPEED, SCAN_TIME);
    alignTime(alignTimeFlag);
    // 显示日期
#if DEBUG_FLAG == 1
    Serial.println("显示当前日期");
#endif
    time.getTime();
    nixie.setShift(utils.getTens(time.timeData.month),
                   utils.getUnits(time.timeData.month),
                   utils.getTens(time.timeData.day),
                   utils.getUnits(time.timeData.day), SCAN_SPEED, SCAN_TIME);
    alignTime(alignTimeFlag);
    // 显示年份
#if DEBUG_FLAG == 1
    Serial.println("显示当前年份");
#endif
    time.getTime();
    nixie.setShift(2, 0, utils.getTens(time.timeData.year),
                   utils.getUnits(time.timeData.year), SCAN_SPEED, SCAN_TIME);
    alignTime(alignTimeFlag);
    // 每 10 分钟做阴极保护
    if (time.getTime().minute % 10 == 0) {
#if DEBUG_FLAG == 1
        Serial.println("执行阴极保护");
#endif
        nixie.setProtect(SCAN_TIME / 5);
        alignTime(alignTimeFlag);
    }
}
