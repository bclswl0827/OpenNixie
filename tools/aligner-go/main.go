package main

import (
	"log"
	"time"

	"github.com/tarm/serial"
)

const (
	BAUDRATE = 9600
	DEVICE   = "/dev/rfcomm0"
)

const (
	CMD_WORD = 0xE0
	ACK_WORD = 0xE1
)

const (
	YEAR_WORD   = 0xF1
	MONTH_WORD  = 0xF2
	DAY_WORD    = 0xF3
	WEEK_WORD   = 0xF4
	HOUR_WORD   = 0xF5
	MINUTE_WORD = 0xF6
	SECOND_WORD = 0xF7
)

func writeCommand(port *serial.Port, data []byte) {
	port.Write([]byte{CMD_WORD})
	time.Sleep(50 * time.Millisecond)

	for _, v := range data {
		port.Write([]byte{v})
		time.Sleep(50 * time.Millisecond)
	}
}

func main() {
	port, err := serial.OpenPort(&serial.Config{
		Name: DEVICE,
		Baud: BAUDRATE,
	})
	if err != nil {
		panic(err)
	}
	defer port.Close()

	for i := 0; i < 7; i++ {
		now := time.Now()
		var (
			year   = now.Year() - 2000
			month  = int(now.Month())
			day    = now.Day()
			week   = int(now.Weekday())
			hour   = now.Hour()
			minute = now.Minute()
			second = now.Second()
		)

		switch i {
		case 0:
			writeCommand(port, []byte{YEAR_WORD, uint8(year)})
			log.Println("Setting year to", year)
		case 1:
			writeCommand(port, []byte{MONTH_WORD, uint8(month)})
			log.Println("Setting month to", month)
		case 2:
			writeCommand(port, []byte{DAY_WORD, uint8(day)})
			log.Println("Setting date to", day)
		case 3:
			writeCommand(port, []byte{WEEK_WORD, uint8(week)})
			log.Println("Setting week to", week)
		case 4:
			writeCommand(port, []byte{HOUR_WORD, uint8(hour)})
			log.Println("Setting hour to", hour)
		case 5:
			writeCommand(port, []byte{MINUTE_WORD, uint8(minute)})
			log.Println("Setting minute to", minute)
		case 6:
			writeCommand(port, []byte{SECOND_WORD, uint8(second)})
			log.Println("Setting second to", second)
		}

		buf := make([]byte, 1)
		_, err = port.Read(buf)
		if err != nil {
			panic(err)
		}

		if buf[0] == ACK_WORD {
			log.Println("OK")
		} else {
			log.Println("Failed")
			return
		}
	}
}
