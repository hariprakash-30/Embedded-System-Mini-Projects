# Working Principle

1. GPIO pins P0.17-P0.19 are configured as outputs. Since the LEDs are active-LOW, writing HIGH turns them OFF.
2. UART0 is configured for 9600 baud, 8 data bits, no parity and one stop bit.
3. The LCD is initialized in 4-bit mode.
4. The program waits for a serial character.
5. The received character is echoed to the PC.
6. Command `1` drives all LED pins LOW and displays the ON status.
7. Command `0` drives all LED pins HIGH and displays the OFF status.
8. Command `2` counts from decimal 0 to 7. The three count bits control the LEDs and are displayed on the LCD as a three-character binary string.
