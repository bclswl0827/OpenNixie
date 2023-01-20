#include <utils.hpp>

// 从两位数中获取十位数
uint_least8_t Utils::getTens(uint_least8_t num) {
    return num / 10;
}

// 从两位数中获取个位数
uint_least8_t Utils::getUnits(uint_least8_t num) {
    return num % 10;
}

// 将字符转为数字
uint_least8_t Utils::getNum(uint_least8_t ch) {
    return ch < 58 ? ch - '0' : 0;
}

// 获取两字符之和
uint_least8_t Utils::getSum(uint_least8_t part_1, uint_least8_t part_2) {
    return (part_1 - '0' < 58 && part_2 - '0' < 58)
               ? 10 * (part_1 - '0') + (part_2 - '0')
               : 0;
}
