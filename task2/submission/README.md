# Task 2: VSDSquadron Mini Board Bring-Up

## Implementation

This firmware was built and flashed on the physical VSDSquadron Mini through
the onboard WCH-Link. It:

- prints a startup message, firmware version, and increasing counter over
  UART;
- toggles the onboard blue user LED once per second; and
- keeps GPIO hardware details in a small API instead of `main.c`.

## GPIO mapping

| Physical label | Firmware GPIO |
|---|---|
| `L1-GPIO` | `PD6` (`GPIOD`, `GPIO_Pin_6`) |

The datasheet identifies the onboard user LED as `PD6`, and the board labels
it `L1-GPIO`. L1 was selected because it provides a visible GPIO test without
external components.

## UART output

After startup, the firmware prints:

```text
=== VSDSquadron Mini boot ===
Firmware version: 1.0.0
VSDSquadron Mini | FW 1.0.0 | Counter: 0
VSDSquadron Mini | FW 1.0.0 | Counter: 1
...
```

The counter increases once per second. PlatformIO Monitor displays the output
at 115200 baud, 8-N-1, through the WCH-Link serial interface.

## Firmware files

- `main.c`: startup, UART messages, counter, timing, and GPIO API calls.
- `gpio.h`: public declarations for `gpio_init()`, `gpio_set()`, and
  `gpio_clear()`.
- `gpio.c`: PD6 configuration and GPIO SDK operations.

`main.c` does not directly manipulate GPIO registers or contain board-specific
GPIO pin definitions.

## Build, flash, and monitor

The recorded workflow used the VS Code PlatformIO extension and the working
PlatformIO project containing these source files:

1. Select **Build** under the `vsdsquadronMini` tasks.
2. Connect the board with a USB data cable.
3. Select **Upload and Monitor**.
4. View the UART output in **Monitor**.

## Reset behavior

During **Upload and Monitor**, the PlatformIO terminal showed `Verified OK` and
`Resetting Target`. The UART boot banner and counter starting at zero appeared
after that automatic reset.


## Evidence and debugging record

- [Task 2 evidence](evidence.md): build, flash, UART, physical-board, and GPIO
  proof.
- [Linux debugging and fix journey](debugging/LINUX_DEBUGGING_JOURNEY.md): separate
  record of the build error and Linux USB/serial permission fixes.
