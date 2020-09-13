
// This library is for the Surenoo 16x2 RGB LCD display.
// The LCD contains a AIP31068 chip for the LCD and a
// PCA9633 chip for the RGB. But only 3 are connected.
// Both libraries are standard available but for more
// easy use they are combined. The C++/C I kept as much
// original but unnecessary routines I have left.
// Variables can be changed in the .h file.

#include <Surenoo.h>
#include <Wire.h>

SURENOO Surenoo; 

void setup()
{
     Surenoo.init();
     Surenoo.clearlcd();
     Surenoo.setCursorlcd(0,0);
     Surenoo.setrgb(BLACK);
     Surenoo.blinklcd();
     Surenoo.print("  Surenoo.h  ");
     Surenoo.setCursorlcd(0,1);
     Surenoo.print("   by PAoAG  ");
     delay(5000);
     Surenoo.noBlinklcd();
     Surenoo.noCursorlcd();
}

void loop()
{
     for (int z=0; z<5; z++)
     {
         Surenoo.setrgb(BLUE);
         delay(500);
         Surenoo.setrgb(RED);
         delay(500);
     }

     Surenoo.setrgb(WHITE);
     Surenoo.blinkrgb(12);
     delay(5000);
     Surenoo.noblinkrgb();
     Surenoo.setrgb(255,128,0);

     for (int x=255; x>0; x--)
     {
         Surenoo.setgrouppwm(x);
         delay(10);
     }

     Surenoo.noDisplaylcd();
     Surenoo.setrgb(0,128,128);

     for (int x=0; x<255; x++)
     {
         Surenoo.setgrouppwm(x);
         delay(10);  
     }

     for (int x=0; x<10; x++)
     {
         Surenoo.noDisplaylcd();
         delay(250);
         Surenoo.displaylcd();
         delay(250);
     }

     for (int x=0; x<10; x++)
     {
         Surenoo.noDisplaylcd();
         Surenoo.setrgb(LIGHTBLUE);
         delay(750);
         Surenoo.displaylcd();
         Surenoo.setrgb(PINK);
         delay(750);
     }
     
     Surenoo.clearlcd();
     
     for (int z=0; z<16; z++)
     {
         Surenoo.setCursorlcd (z,0);
         Surenoo.print("x");
         delay(500);
     }
     
     for (int z=0; z<16; z++)
     {
         Surenoo.setCursorlcd (z,1);
         Surenoo.print("x");
         delay(500);
     }
}