# Raspberry Pi Pico Pin Specification

This document provides a concise summary of the Raspberry Pi Pico's pin functions and layout.  
Useful for firmware development, hardware interfacing, and reference in embedded projects.

## Power Pins

| Pin Name   | Description                        |
|------------|------------------------------------|
| VBUS       | 5V input from USB connector        |
| VSYS       | Main system input (1.8V–5.5V)      |
| 3V3(OUT)   | 3.3V regulated output (~300mA max) |
| GND        | Ground (multiple pins available)   |

## GPIO Pins

- 26 multi-function GPIOs: `GPIO0` to `GPIO28`  
  (Note: `GPIO23–28` are used internally for flash and may not be available)
- Each GPIO supports:
  - Digital Input/Output
  - PWM (Programmable)
  - SPI / I2C / UART (configurable via software)
  - Interrupts
- GPIO26–28 support ADC input

## Analog Inputs

| GPIO Pin | ADC Channel | Notes                     |
|----------|-------------|---------------------------|
| GPIO26   | ADC0        |                           |
| GPIO27   | ADC1        |                           |
| GPIO28   | ADC2        |                           |
| —        | ADC4        | Internal temperature sensor |

## Communication Interfaces

- **SPI**: 2 controllers (configurable on GPIOs)
- **I2C**: 2 controllers (configurable on GPIOs)
- **UART**: 2 controllers (configurable on GPIOs)
- **USB 1.1**: Device mode via micro USB port

## Debug Interface

| Function | GPIO Pin |
|----------|----------|
| SWDIO    | GPIO24   |
| SWCLK    | GPIO25   |

## Onboard Peripherals

- **LED**: Connected to `GPIO25`

---

> 📌 For a full pinout diagram, refer to the official Raspberry Pi Pico datasheet:  
> https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf


# Raspberry Pi Pico Pinout Table (1–40)

This table lists the Raspberry Pi Pico 40-pin header in physical pin order, showing each pin's default function.
# Raspberry Pi Pico Pinout (1–40, Single Column)

This table lists all 40 pins of the Raspberry Pi Pico in physical order with their default functions.
# Raspberry Pi Pico Pinout 1–40

This document lists the **Raspberry Pi Pico** 40-pin header in physical pin order (1 → 40).  
Each row shows the **Pin**, **Name**, and **Primary Function(s)**. Use this file as a quick reference for wiring, firmware mapping, or documentation.

---

| Pin | Name     | Primary Function(s) |
|-----|----------|---------------------|
| 1   | GP0      | UART0_TX; I2C0_SDA; SPI0_RX |
| 2   | GP1      | UART0_RX; I2C0_SCL; SPI0_CSn |
| 3   | GND      | Ground |
| 4   | GP2      | I2C1_SDA; SPI0_SCK |
| 5   | GP3      | I2C1_SCL; SPI0_TX |
| 6   | GP4      | UART1_TX; I2C0_SDA; SPI0_RX |
| 7   | GP5      | UART1_RX; I2C0_SCL; SPI0_CSn |
| 8   | GND      | Ground |
| 9   | GP6      | I2C1_SDA; SPI0_SCK |
| 10  | GP7      | I2C1_SCL; SPI0_TX |
| 11  | GP8      | SPI1_RX |
| 12  | GP9      | SPI1_CSn |
| 13  | GND      | Ground |
| 14  | GP10     | I2C0_SDA; SPI1_SCK |
| 15  | GP11     | I2C0_SCL; SPI1_TX |
| 16  | GP12     | UART0_TX; I2C0_SDA |
| 17  | GP13     | UART0_RX; I2C0_SCL |
| 18  | GND      | Ground |
| 19  | GP14     | I2C1_SCK; SPI1_CSn |
| 20  | GP15     | I2C1_TX; SPI1_TX |
| 21  | GP16     | SPI0_RX; I2C0_SDA; UART0_TX |
| 22  | GP17     | SPI0_CSn; I2C0_SCL; UART0_RX |
| 23  | GND      | Ground |
| 24  | GP18     | SPI0_SCK; I2C1_SDA |
| 25  | GP19     | SPI0_TX; I2C1_SCL |
| 26  | GP20     | I2C0_SDA |
| 27  | GP21     | I2C0_SCL |
| 28  | GND      | Ground |
| 29  | GP22     | GPIO; PWM |
| 30  | RUN      | Reset active low |
| 31  | GP26     | ADC0; GPIO |
| 32  | GP27     | ADC1; GPIO |
| 33  | GP28     | ADC2; GPIO |
| 34  | GND      | Ground |
| 35  | ADC_VREF | ADC reference voltage |
| 36  | 3V3OUT   | 3.3V regulated output |
| 37  | 3V3_EN   | 3.3V enable control |
| 38  | GND      | Ground |
| 39  | VSYS     | System input voltage 1.8–5.5V |
| 40  | VBUS     | USB 5V input |

---

**Notes**

- LED is connected to **GP25** (onboard user LED).  
- ADC channels are **GP26 = ADC0**, **GP27 = ADC1**, **GP28 = ADC2**. **ADC_VREF** provides the analog reference.  
- Pulling **RUN** to ground resets the RP2040.  
- **3V3_EN** controls the on-board 3.3V regulator enable.  
- Many GPIOs are multi-function and can be reassigned to UART, SPI, I2C, PWM, or PIO via software; consult the RP2040 datasheet for alternate function mappings and electrical limits.

---

If you want this file named or adjusted for a specific repository README style, or converted to CSV or a C header with `#define` macros, tell me the desired filename and format.

> 📌 Notes:
> - `GP28` (ADC2) is not on the 40-pin header; it's on the debug header.
> - `SWDIO` and `SWCLK` for debugging are also on the debug header.
> - All GPIOs support digital I/O and PWM by default.


> 📝 Note:
> - `GP28` (ADC2) is not on the 40-pin header; it's on the debug header.
> - `SWDIO` and `SWCLK` are also on the debug header, not listed here.
> - All GPIOs support digital I/O and PWM by default.


