# aligner-go

This is an OpenNixie time calibration program written in Go.

## Quick Start

On a Bluetooth-equipped Linux device (such as most laptops running Debian 11), then use the rfcomm tool to connect to OpenNixie.

Assuming the bluetooth has been paired and its MAC address is `00:00:00:00:00:00` as an example, an example is given below:

```bash
$ sudo rfcomm connect 0 00:00:00:00:00:00
```

Unsurprisingly, a device can be found in `/dev/rfcomm0`:

```bash
$ ls -l /dev/rfcomm0
crw-rw---- 1 root dialout 216, 0  9月  9 21:59 /dev/rfcomm0
```

Then, compile and run this demo:

```bash
$ go build
$ ./aligner-go
```
