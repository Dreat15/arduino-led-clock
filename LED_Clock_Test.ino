#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <FastLED.h>
#include <fastpin.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <fastspi.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>

/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
#define LEDStripPin A0 // Pin used for the data to the LED strip
#define numLEDs 60 // Number of LEDs in strip
struct CRGB leds[numLEDs];
int currentLed = 0;
int minutes = 0;
int stunde = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  LEDS.addLeds<WS2811, LEDStripPin, GRB>(leds, numLEDs);
}

// the loop function runs over and over again forever
void loop() {
                      // wait for a second

  // clear LED array
  

    currentLed++;

    if(currentLed >= numLEDs)
    {
        memset(leds, 0, numLEDs * 3);
        currentLed = 0;
        
        minutes++;
        if(minutes >= numLEDs)
        {
            minutes = 0;
            stunde++;
        }

        if(minutes == 12 || minutes == 24
        || minutes == 36 || minutes == 48)
        {
            stunde++;
        }
        if(stunde >= numLEDs)
        {
            stunde = 0;
        } 
    }

    
    leds[currentLed].r = 0;
    leds[currentLed].g = 10;
    leds[currentLed].b = 40;
    leds[minutes].r = 40;
    leds[minutes].g = 10;
    leds[minutes].b = 0;
    leds[stunde].r = 10;
    leds[stunde].g = 40;
    leds[stunde].b = 0;

    if(currentLed == minutes)
    {
        leds[minutes].r = 40;
        leds[minutes].g = 10 + 10;
        leds[minutes].b = 0 + 40;
    }
    if(minutes == stunde)
    {
        leds[stunde].r = 40 + 10;
        leds[stunde].g = 10 + 40;
        leds[stunde].b = 0;
    }
    if(currentLed == stunde)
    {
        leds[stunde].r = 10;
        leds[stunde].g = 40 + 10;
        leds[stunde].b = 0 + 40;
    }
    
    LEDS.show();
    delay(1000);
}