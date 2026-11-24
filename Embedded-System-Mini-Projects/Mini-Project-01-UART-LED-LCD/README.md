# Mini Project 01: UART Controlled LED with LCD Status

## 1. Overview

This project receives single-character commands from a PC serial terminal through UART0 on an LPC21xx-family ARM7 microcontroller. The received command controls three active-LOW LEDs and the 16x2 LCD displays the current operation.

The circuit image supplied during project preparation labels the MCU as **LPC2138**. Confirm that LPC2138 is the actual target device used in your lab. The source includes `<LPC21xx.h>` and must be built with a compatible device header and startup/project configuration.

## 2. Features

| UART command | Operation |
|---|---|
| `1` | Turns ON all three LEDs and displays `TURN ON ALL LEDS` |
| `0` | Turns OFF all three LEDs and displays `TURN OFF ALL LEDS` |
| `2` | Displays binary values 000 through 111 and drives the LEDs accordingly |

The received character is also echoed back to the serial terminal.

## 3. Hardware

- LPC21xx-family ARM7 microcontroller (diagram supplied shows LPC2138)
- Three LEDs with individual current-limiting resistors
- 16x2 character LCD compatible with the selected supply voltage
- USB-to-UART adapter or Proteus Virtual Terminal
- Regulated supply and common ground
- Crystal/clock and reset circuitry as required by the target board

## 4. Pin mapping used by the source

### UART0
- P0.0 / TXD0 -> serial terminal RXD
- P0.1 / RXD0 <- serial terminal TXD
- Connect grounds together.

### LEDs
- P0.17 -> LED 1
- P0.18 -> LED 2
- P0.19 -> LED 3

The source assumes active-LOW LED wiring: the LED is ON when its GPIO output is LOW. Use a current-limiting resistor for each LED.

### LCD in 4-bit mode
The driver assumes:
- RS -> P1.17
- RW -> P1.18
- EN -> P1.19
- D4 -> P1.20
- D5 -> P1.21
- D6 -> P1.22
- D7 -> P1.23

The LCD's R/W pin is driven LOW for read/write timing in this driver; the code writes commands/data only. Verify the exact wiring against your circuit.

## 5. Software files

- `Core/main.c` – command processing and LED control
- `Core/uart_driver.c/.h` – UART0 initialization, transmit and receive functions
- `Core/lcd_driver.c/.h` – 4-bit LCD driver
- `Core/delay.c/.h` – Timer0-based delay functions

## 6. Clock assumptions

The driver configuration currently assumes:
- CCLK = 60 MHz
- VPBDIV = 1, so PCLK = CCLK = 60 MHz
- UART baud rate = 9600

If your board uses a different crystal, PLL setup or peripheral clock, update the clock configuration and UART/timer calculations accordingly. The timer driver in this package uses the stated 60 MHz PCLK assumption.

## 7. Build and run

1. Open your Keil µVision project for the exact LPC21xx device.
2. Add `main.c`, `uart_driver.c`, `lcd_driver.c`, and `delay.c` to the project.
3. Ensure the matching header files are available in the include path.
4. Confirm the startup file, linker/scatter settings, oscillator and PLL configuration.
5. Build the project and program the board.
6. Open a serial terminal at 9600 baud, 8 data bits, no parity, 1 stop bit (8-N-1).
7. Send `1`, `0`, or `2`.

This repository does not include a generated Keil project file because the exact device/clock/startup configuration has not yet been confirmed. Add your actual `.uvprojx` and related project files in `Keil-Project/` after confirming the target.

## 8. Circuit review notes

The supplied schematic is a useful draft for the signal mapping, but make these changes/checks before treating it as a final circuit:

1. Add a current-limiting resistor in series with each LED. Do not connect an LED directly between +3.3 V and a GPIO pin.
2. LCD pin 1 (VSS) must connect to ground, pin 2 (VDD) to a supply supported by the LCD module, and pin 3 (V0/VEE) to a contrast adjustment circuit (commonly the wiper of a potentiometer). Do not tie VSS, VDD and V0 together.
3. Ensure the LCD module supports the chosen supply voltage and that its logic levels are compatible with the MCU.
4. Cross UART connections: MCU TXD0 to terminal RXD, and MCU RXD0 to terminal TXD. Share ground.
5. Confirm the MCU oscillator/clock and reset configuration in Proteus or on the physical board.
6. The schematic labels the MCU LPC2138; verify this matches the actual device selected in Keil and the hardware board.

## 9. Limitations

- Command input is blocking: the program waits inside `uart0_rx()` until a character arrives.
- The binary count is a blocking sequence with a 2-second delay for each value.
- The timer and UART drivers depend on the clock assumptions documented above.
- The LCD initialization sequence and wiring should be validated with the actual LCD module.

## 10. License

This project is released under the MIT License. See the repository-level `LICENSE` file.
