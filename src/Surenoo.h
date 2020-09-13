#ifndef _SURENOO_H
#define _SURENOO_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
 #include "pins_arduino.h"
 #include "WConstants.h"
#endif

#include <Wire.h>
#include <inttypes.h>
#include "Print.h" 

#define LCD_ADDRESS 0x3E
#define RGB_ADDRESS 0x60

// rgb color scheme
#define BLUE 255,0,0
#define GREEN 0,255,0
#define RED 0,0,255
#define LIGHTBLUE 255,255,0
#define PINK 255,0,255
#define LIGHTGREEN 0,255,255
#define BLACK 0,0,0
#define WHITE 255,255,255

// commands rgb
#define AI2			(0x80) // mask for AI2
#define AI1			(0x40) // mask for AI1
#define AI0			(0x20) // mask for AI0

#define INCOFF			(0x00) // AI2:0 000 no auto increment
#define INCALL			(0x80) // AI2:0 100 auto inc all registers
#define INCIND			(0xA0) // AI2:0 101 auto inc individual pwm registers
#define INCGBL			(0xC0) // AI2:0 110 auto inc global registers
#define INCINDGBL		(0xE0) // AI2:0 111 auto inc individual and global registers

// register definitions Datasheet page 11
#define MODE1			(0x00) // mode register 1
#define MODE2			(0x01) // mode register 2
#define PWM0			(0x02) // PWM0 brightness control led0
#define PWM1			(0x03) // PWM0 brightness control led0
#define PWM2			(0x04) // PWM0 brightness control led0
#define GRPPWM			(0x06) // group brightness (duty cycle)
#define GRPFREQ			(0x07) // group frequency
#define LEDOUT			(0x08) // LED output state
#define SUBADR1			(0x09) // i2c bus sub address 1
#define SUBADR2			(0x0A) // i2c bus sub address 1
#define SUBADR3			(0x0B) // i2c bus sub address 1
#define ALLCALLADR		(0x0C) // LED All Call i2c address

// MODE1 definitions
#define SLEEP			(0x10) // bit 4, low power mode enable, RW
#define SUB1			(0x08) // bit 3, PCA9633 responds to sub address 1
#define SUB2			(0x04) // bit 2, PCA9633 responds to sub address 2
#define SUB3			(0x02) // bit 1, PCA9633 responds to sub address 3
#define ALLCALL			(0x01) // bit 0, PCA9633 responds to all call address

// MODE2 definitions
#define DMBLINK			(0x20) // bit 5, group control dim or blink
#define INVRT			(0x10) // bit 4, output logic invert (1=yes, 0=no)
#define OCH			(0x08) // bit 3, 0=output change on stop, 1=output change on ACK
#define OUTDRV			(0x04) // bit 2, output drivers 0=open drain, 1=totem poll - push pull
#define OUTNE1			(0x02) // bit 1, 2 bits see page 13, 16 pin device only
#define OUTNE0			(0x01) // bit 0, see above

// linearized brightness values
const size_t len_ledLinear = 256;
const uint8_t ledLinear[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05,
0x05, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x08, 0x08, 0x08, 0x09, 0x09, 0x0A, 0x0A, 0x0B, 0x0B,
0x0C, 0x0C, 0x0D, 0x0D, 0x0E, 0x0F, 0x0F, 0x10, 0x11, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x26, 0x27, 0x29, 0x2B, 0x2C,
0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3A, 0x3C, 0x3E, 0x40, 0x43, 0x45, 0x47, 0x4A, 0x4C, 0x4F,
0x51, 0x54, 0x57, 0x59, 0x5C, 0x5F, 0x62, 0x64, 0x67, 0x6A, 0x6D, 0x70, 0x73, 0x76, 0x79, 0x7C,
0x7F, 0x82, 0x85, 0x88, 0x8B, 0x8E, 0x91, 0x94, 0x97, 0x9A, 0x9C, 0x9F, 0xA2, 0xA5, 0xA7, 0xAA,
0xAD, 0xAF, 0xB2, 0xB4, 0xB7, 0xB9, 0xBB, 0xBE, 0xC0, 0xC2, 0xC4, 0xC6, 0xC8, 0xCA, 0xCC, 0xCE,
0xD0, 0xD2, 0xD3, 0xD5, 0xD7, 0xD8, 0xDA, 0xDB, 0xDD, 0xDE, 0xDF, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5,
0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xED, 0xEE, 0xEF, 0xEF, 0xF0, 0xF1, 0xF1, 0xF2,
0xF2, 0xF3, 0xF3, 0xF4, 0xF4, 0xF5, 0xF5, 0xF6, 0xF6, 0xF6, 0xF7, 0xF7, 0xF7, 0xF8, 0xF8, 0xF8,
0xF9, 0xF9, 0xF9, 0xF9, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFC,
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD,
0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF};

// commands lcd
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00
#define LCD_COLS 0x16
#define LCD_ROWS 0x02

#define Rs B01000000  // Register select bit


class SURENOO : public Print {
  public:
    SURENOO();
    void beginrgb(); // set i2c address
    void setrgb(uint8_t p0, uint8_t p1, uint8_t p2); // set all four pwm reg at once
    void init(); // reset chip to desired startup state
    void blinkrgb(uint8_t blinkspeed);
    void noblinkrgb(void);
    void setgrouppwm(uint8_t pwm);

    uint8_t linearize(uint8_t pwm); // read from linearize lookup table and return value

private:
  uint8_t _pcaAddr;

public:
SURENO();
  void clearlcd();
  void homelcd();
  void noDisplaylcd();
  void displaylcd();
  void noBlinklcd();
  void blinklcd();
  void noCursorlcd();
  void cursorlcd();
  void scrollDisplayLeftlcd();
  void scrollDisplayRightlcd();
  void printLeftlcd();
  void printRightlcd();
  void leftToRightlcd();
  void rightToLeftlcd();
  void shiftIncrementlcd();
  void shiftDecrementlcd();
  void autoscrolllcd();
  void noAutoscrolllcd(); 
  void createCharlcd(uint8_t, uint8_t[]);
  void createCharlcd(uint8_t location, const char *charmap);
  void setCursorlcd(uint8_t, uint8_t);
  void commandlcd(uint8_t);
  void initlcd();
 
private:


#if defined(ARDUINO) && ARDUINO >= 100
  virtual size_t write(uint8_t);
#else
  virtual void write(uint8_t);
#endif


  void sendlcd(uint8_t, uint8_t);
  void write4bitslcd(uint16_t);
  void write8bitslcd(uint16_t);
  void controllerWritelcd(uint16_t);

  uint8_t _Addr;
  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;
  uint8_t _numlines;
  bool _oled = false;
  uint8_t _cols;
  uint8_t _rows;
};


#endif // end _SURENOO_H
