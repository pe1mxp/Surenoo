
#include <Wire.h>
#include <inttypes.h>
#include "Surenoo.h"

#if ARDUINO >= 100
    #include "Arduino.h"
    inline size_t SURENOO::write(uint8_t value)
    {
           sendlcd(value, 1);
           return 1;
    }
#else
    #include "WProgram.h"
    inline void SURENOO::write(uint8_t value)
    {
           sendlcd(value, 1);
    }
#endif

SURENOO::SURENOO()
{
}

void SURENOO::controllerWritelcd(uint16_t _data)
{
     Wire.beginTransmission(_Addr);
     Wire.write((_data >> 8) & 0xFF);
     Wire.write((_data >> 0) & 0xFF);
     Wire.endTransmission();   
}

static void _i2c_write(uint8_t address, uint8_t cmd, uint8_t data)
{
       Wire.beginTransmission(address);
       Wire.write(cmd);
       Wire.write(data);
       Wire.endTransmission();
}

uint8_t SURENOO::linearize(uint8_t pwm)
{
        uint8_t result = pgm_read_byte(ledLinear + pwm);
        return result;
}

void SURENOO::init(void)
{
     uint8_t m1 = 0x00;
     uint8_t m2 = OUTDRV;
     uint8_t ldout = 0xFF;
     _pcaAddr = RGB_ADDRESS;

     _i2c_write(_pcaAddr, MODE1, m1);
     _i2c_write(_pcaAddr, MODE2, m2);
     _i2c_write(_pcaAddr, LEDOUT, ldout);

     _Addr = LCD_ADDRESS;
     _cols = LCD_COLS;
     _rows = LCD_ROWS;

     Wire.begin();
     _displayfunction = LCD_2LINE | LCD_5x8DOTS | LCD_8BITMODE;
     _numlines = _rows;

     commandlcd(LCD_FUNCTIONSET | _displayfunction);
     delayMicroseconds(4500);  // wait more than 4.1ms

     commandlcd(LCD_FUNCTIONSET | _displayfunction);
     delayMicroseconds(150);

     commandlcd(LCD_FUNCTIONSET | _displayfunction);

     commandlcd(LCD_FUNCTIONSET | _displayfunction);  

     _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
     displaylcd();
     clearlcd();
    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	
     commandlcd(LCD_ENTRYMODESET | _displaymode);
	
     homelcd();
}

void SURENOO::setrgb(uint8_t p0, uint8_t p1, uint8_t p2)
{
     _i2c_write(_pcaAddr, PWM0, linearize(p0));
     _i2c_write(_pcaAddr, PWM1, linearize(p1));
     _i2c_write(_pcaAddr, PWM2, linearize(p2));
}

void SURENOO::blinkrgb(uint8_t blinkspeed)
{
     _i2c_write(_pcaAddr, MODE2,   ((OUTDRV) | (DMBLINK)));
     _i2c_write(_pcaAddr, GRPFREQ, blinkspeed);
     _i2c_write(_pcaAddr, GRPPWM,  0x7F);
}

void SURENOO::noblinkrgb(void)
{
     _i2c_write(_pcaAddr, MODE2,   OUTDRV);
     _i2c_write(_pcaAddr, GRPFREQ, 0x00);
     _i2c_write(_pcaAddr, GRPPWM,  0xFF);
}

void SURENOO::setgrouppwm(uint8_t pwm)
{
     _i2c_write(_pcaAddr, GRPPWM, pwm);
}



void SURENOO::initlcd()
{
     _Addr = LCD_ADDRESS;
     _cols = LCD_COLS;
     _rows = LCD_ROWS;

     Wire.begin();
     _displayfunction = LCD_2LINE | LCD_5x8DOTS | LCD_8BITMODE;
     _numlines = _rows;

     commandlcd(LCD_FUNCTIONSET | _displayfunction);
     delayMicroseconds(4500);  // wait more than 4.1ms

     commandlcd(LCD_FUNCTIONSET | _displayfunction);
     delayMicroseconds(150);

     commandlcd(LCD_FUNCTIONSET | _displayfunction);

     commandlcd(LCD_FUNCTIONSET | _displayfunction);  

     _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
     displaylcd();
     clearlcd();
    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	
     commandlcd(LCD_ENTRYMODESET | _displaymode);
	
     homelcd();
}

void SURENOO::clearlcd()
{
     commandlcd(LCD_CLEARDISPLAY);
     delayMicroseconds(2000);
}

void SURENOO::homelcd()
{
     commandlcd(LCD_RETURNHOME);
     delayMicroseconds(2000); 
}

void SURENOO::setCursorlcd(uint8_t col, uint8_t row)
{
     int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
     if ( row > _numlines )
     {
        row = _numlines-1;
     }
     commandlcd(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void SURENOO::noDisplaylcd()
{
     _displaycontrol &= ~LCD_DISPLAYON;
     commandlcd(LCD_DISPLAYCONTROL | _displaycontrol);
}

void SURENOO::displaylcd()
{
     _displaycontrol |= LCD_DISPLAYON;
     commandlcd(LCD_DISPLAYCONTROL | _displaycontrol);
}

void SURENOO::noCursorlcd()
{
     _displaycontrol &= ~LCD_CURSORON;
     commandlcd(LCD_DISPLAYCONTROL | _displaycontrol);
}

void SURENOO::cursorlcd()
{
     _displaycontrol |= LCD_CURSORON;
     commandlcd(LCD_DISPLAYCONTROL | _displaycontrol);
}

void SURENOO::noBlinklcd()
{
     _displaycontrol &= ~LCD_BLINKON;
     commandlcd(LCD_DISPLAYCONTROL | _displaycontrol);
}

void SURENOO::blinklcd() {
    _displaycontrol |= LCD_BLINKON;
    commandlcd(LCD_DISPLAYCONTROL | _displaycontrol);
}

void SURENOO::scrollDisplayLeftlcd(void)
{
     commandlcd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void SURENOO::scrollDisplayRightlcd(void)
{
     commandlcd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void SURENOO::leftToRightlcd(void)
{
     _displaymode |= LCD_ENTRYLEFT;
     commandlcd(LCD_ENTRYMODESET | _displaymode);
}

void SURENOO::rightToLeftlcd(void)
{
     _displaymode &= ~LCD_ENTRYLEFT;
     commandlcd(LCD_ENTRYMODESET | _displaymode);
}

void SURENOO::autoscrolllcd(void)
{
     _displaymode |= LCD_ENTRYSHIFTINCREMENT;
     commandlcd(LCD_ENTRYMODESET | _displaymode);
}

void SURENOO::noAutoscrolllcd(void)
{
	_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	commandlcd(LCD_ENTRYMODESET | _displaymode);
}

void SURENOO::createCharlcd(uint8_t location, uint8_t charmap[])
{
     location &= 0x7; // we only have 8 locations 0-7
     commandlcd(LCD_SETCGRAMADDR | (location << 3));
     for (int i=0; i<8; i++)
     {
         write(charmap[i]);
     }
}

void SURENOO::createCharlcd(uint8_t location, const char *charmap)
{
     location &= 0x7; // we only have 8 locations 0-7
     commandlcd(LCD_SETCGRAMADDR | (location << 3));
     for (int i=0; i<8; i++)
     {
         write(pgm_read_byte_near(charmap++));
     }
}

void SURENOO::commandlcd(uint8_t value)
{
     sendlcd(value, 0);
}

void SURENOO::sendlcd(uint8_t value, uint8_t mode)
{
     uint16_t rs = mode != 0? Rs << 8: 0;
     write8bitslcd(rs | value); 
}

void SURENOO::write4bitslcd(uint16_t value)
{
     controllerWritelcd((value & 0xFF00) | (value & 0x00FF) << 4);
}

void SURENOO::write8bitslcd(uint16_t value)
{
     controllerWritelcd(value);
}
