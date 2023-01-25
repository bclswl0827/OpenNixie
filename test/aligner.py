"""
这是一个对时工具原型，功能如下

 1. 生成时间报文
 2. 发送时间报文
 3. 发送心跳报文

由于单片机需要解析时间报文
导致写入芯片的时间慢一秒
所以需要在程序中对秒数做 +1 秒的补偿
"""

import serial
import time
import datetime


def main():
    s = serial.Serial(
        # sudo rfcomm connect 0 1C:24:2C:11:7B:B6
        #port="/dev/rfcomm1",
        port="/dev/ttyUSB0",
        baudrate=9600,
        timeout=1,
    )

    while(True):
        # 生成时间报文
        time_data = (
            datetime.datetime.now() +
            # 对秒数做 1 秒补偿
            datetime.timedelta(seconds=1)
        ).strftime("$%y,%m,%d,%H,%M,%S,") + \
            str(
                int(datetime.datetime.now().strftime("%w"))+1
        ) + "*\n"
        # 发送时间报文
        s.write(time_data.encode('utf-8'))
        # 休眠 0.1 秒
        time.sleep(0.1)
        # 发送心跳报文
        s.write(b'$PONG*\n')
        # 休眠 0.1 秒
        time.sleep(0.1)


if __name__ == '__main__':
    main()
