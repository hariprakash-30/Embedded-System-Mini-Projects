# Project Overview

The project uses UART0 to receive commands from a PC. The microcontroller interprets the characters `1`, `0`, and `2` to control three active-LOW LEDs and show the corresponding status or binary count on a 16x2 LCD.

## Objectives

- Understand UART serial communication.
- Configure GPIO pins as outputs.
- Interface a character LCD in 4-bit mode.
- Use bitwise operations to display a 3-bit binary count.
- Organize embedded C code into reusable drivers and application code.
