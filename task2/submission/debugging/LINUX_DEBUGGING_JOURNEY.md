# Linux Debugging and Fix Journey

This document records the build, upload, and serial-monitor problems encountered
on Linux and the fixes that were tested.

## 1. Firmware build error

The first build failed because `NVIC_PriorityGroup_2` was unavailable in the
selected SDK. It was replaced with `NVIC_PriorityGroup_1`, after which the
firmware built successfully.

![Initial firmware build error](debug-evidence/01-firmware-build-error.png)

## 2. Upload permission error

When **Upload** was selected, PlatformIO started OpenOCD internally to access
the WCH-Link programmer. The upload failed with:

```text
libusb_open() failed with LIBUSB_ERROR_ACCESS
Error: open failed
```

![Upload permission error](debug-evidence/02-upload-libusb-access-error.png)

`lsusb` confirmed that Linux detected the WCH-Link as USB device `1a86:8010`.

![WCH-Link detected by Linux](debug-evidence/03-wch-link-detected-by-lsusb.png)

The raw USB device node was owned by `root:root`, and the signed-in user did not
have write access.

![USB permissions before the fix](debug-evidence/04-raw-usb-permissions-before-fix.png)

A udev rule was installed for the WCH-Link:

```udev
SUBSYSTEM=="usb", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="8010", MODE="0660", GROUP="plugdev", TAG+="uaccess"
```

The rules were reloaded, and the board was unplugged and reconnected. The USB
node then used group `plugdev` and allowed user read/write access.

![USB permissions after the udev fix](debug-evidence/05-udev-rule-and-usb-permissions-fixed.png)

The next upload completed programming, verification, and reset successfully.

![Successful upload](debug-evidence/06-upload-success-after-udev-fix.png)

## 3. Serial-monitor permission error

PlatformIO detected the WCH-Link serial interface at `/dev/ttyACM0`.

![Detected serial device](debug-evidence/07-wch-link-serial-device.png)

Opening **Monitor** initially failed with:

```text
Permission denied: '/dev/ttyACM0'
```

![Monitor permission error](debug-evidence/08-monitor-permission-denied.png)

The user was added to `dialout` and logged out and back in, but Monitor still
received the permission error. An explicit ACL was then applied to the current
serial device:

```bash
sudo setfacl -m u:vshbit:rw /dev/ttyACM0
```

The resulting ACL included `user:vshbit:rw-`.

![Serial ACL fix](debug-evidence/09-tty-acl-workaround.png)

> **Note:** This ACL applies to the current `/dev/ttyACM0` device instance and
> may need to be reapplied after reconnecting the board.

## 4. Final result

After the ACL fix, PlatformIO Monitor opened at 115200 baud. **Upload and
Monitor** showed successful programming, automatic reset, the firmware boot
banner, and consecutive counter lines.

![Final successful UART monitor](../evidence/03-final-gpio-api-uart.png)
