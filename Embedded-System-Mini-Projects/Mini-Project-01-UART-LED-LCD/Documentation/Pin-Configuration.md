# Pin Configuration

| Function | MCU pin | Notes |
|---|---|---|
| UART0 TX | P0.0 / TXD0 | Connect to terminal RXD |
| UART0 RX | P0.1 / RXD0 | Connect to terminal TXD |
| LED 1 | P0.17 | Active-LOW |
| LED 2 | P0.18 | Active-LOW |
| LED 3 | P0.19 | Active-LOW |
| LCD RS | P1.17 | GPIO output |
| LCD RW | P1.18 | Held LOW by driver |
| LCD EN | P1.19 | GPIO output |
| LCD D4 | P1.20 | 4-bit data |
| LCD D5 | P1.21 | 4-bit data |
| LCD D6 | P1.22 | 4-bit data |
| LCD D7 | P1.23 | 4-bit data |

Check the exact package pin numbers and pin multiplexing against the datasheet for the selected MCU.
