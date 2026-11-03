# HMC849 RF Source Switch

This project uses a Nucleo-F303RE board to control an HMC849 RF switch and toggle the signal path between two states:

- Antenna input
- 50-ohm reference termination

A push button switches the source, and the onboard LED indicates the currently selected state.

## Hardware

- STM32 Nucleo-F303RE
- HMC849 RF switch control interface
- Onboard user button
- Onboard LED

## Pin mapping

- PA0 -> HMC_CTRL
- PA1 -> HMC_EN
- PC13 -> button input
- LED_BUILTIN -> status LED

## Behavior

- Startup defaults to the antenna path.
- Pressing the button toggles between antenna and reference.
- The serial monitor prints the current selection at 115200 baud.

## Build and upload

1. Open the project in PlatformIO.
2. Build the firmware.
3. Upload it to the Nucleo board.
4. Open the serial monitor to observe state changes.

## Notes

This firmware is written using the Arduino framework and is intended for quick RF source switching experiments on the STM32 Nucleo platform.

## RF signal vs. depth

The `rf signal_vs_depth.py` script models tissue contributions to a radiometer signal across depth and frequency, and generates plots for muscle and fat tissue.
