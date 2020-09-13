Library for the Surenoo 16x2 I2C library.

This library is a combination of 2 libraries.
The Serenoo LCD has a AIP31068 chip for driving
the LCD. The RGB leds are driven by a PCA9633 chip.
Both are standard libraries. But the PCA9633 library
is for 4 LED's and the LCD has only 3 LED's. Port 4
of the chip is not connected. So eventually the 4th
port can be used for another using eg. buzzer when
soldered. For noise reducing on the suply line I have
mounted an extra 100nf capacitator between V+ and GND.
