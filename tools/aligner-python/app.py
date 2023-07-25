import serial
import time
import datetime
import logging

BAUDRATE = 9600
DEVICE = "/dev/rfcomm0"

CMD_WORD = 0xE0
ACK_WORD = 0xE1

YEAR_WORD = 0xF1
MONTH_WORD = 0xF2
DAY_WORD = 0xF3
WEEK_WORD = 0xF4
HOUR_WORD = 0xF5
MINUTE_WORD = 0xF6
SECOND_WORD = 0xF7


def write_command(port, data):
    port.write(bytes([CMD_WORD]))
    time.sleep(0.05)

    for v in data:
        port.write(bytes([v]))
        time.sleep(0.05)


def setup_logger():
    logger = logging.getLogger("my_logger")
    logger.setLevel(logging.DEBUG)

    formatter = logging.Formatter("%(asctime)s - %(levelname)s - %(message)s")

    # Output log messages to the console
    console_handler = logging.StreamHandler()
    console_handler.setFormatter(formatter)
    logger.addHandler(console_handler)

    return logger


def main():
    logger = setup_logger()

    try:
        port = serial.Serial(DEVICE, BAUDRATE)
    except serial.SerialException as e:
        logger.exception("Error opening serial port")
        return

    for i in range(7):
        now = datetime.datetime.now()
        year = now.year - 2000
        month = now.month
        day = now.day
        week = now.weekday()
        hour = now.hour
        minute = now.minute
        second = now.second

        if i == 0:
            write_command(port, [YEAR_WORD, year])
            logger.info(f"Setting year to {year}")
        elif i == 1:
            write_command(port, [MONTH_WORD, month])
            logger.info(f"Setting month to {month}")
        elif i == 2:
            write_command(port, [DAY_WORD, day])
            logger.info(f"Setting date to {day}")
        elif i == 3:
            write_command(port, [WEEK_WORD, week])
            logger.info(f"Setting week to {week}")
        elif i == 4:
            write_command(port, [HOUR_WORD, hour])
            logger.info(f"Setting hour to {hour}")
        elif i == 5:
            write_command(port, [MINUTE_WORD, minute])
            logger.info(f"Setting minute to {minute}")
        elif i == 6:
            write_command(port, [SECOND_WORD, second])
            logger.info(f"Setting second to {second}")

        ack = port.read(1)
        if ack[0] == ACK_WORD:
            logger.info("OK")
        else:
            logger.error("Failed")
            return


if __name__ == "__main__":
    main()
