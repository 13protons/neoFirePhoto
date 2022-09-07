/*
 *  Project     FastLED NeoPixel Library
 *  @author     David Madison
 *  @link       github.com/dmadison/FastLED_NeoPixel
 *  @license    MIT - Copyright (c) 2021 David Madison
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

 /**
 * @file    Strandtest.ino
 * @brief   A basic strip test program.
 * @example Strandtest.ino
 * @brief   A basic strip test program.
 * 
 * @details This partially mirrors the behavior of the Adafruit NeoPixel
 * "strandtest" example. Due to licensing issues that example cannot be
 * included in this library, but I recommend trying to modify it yourself with
 * the FastLED NeoPixel alterations.
 *
 * You can find the original example here:
 * https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/strandtest/strandtest.ino
 */

#include <FastLED.h>

#define DATA_PIN    12

#define LED_TYPE    WS2812
#define COLOR_ORDER NEO_GRB + NEO_KHZ800



#define BRIGHTNESS          100


//========./assets/sunset.png======== - generated 1662472339006
 
const int seq_width = 30; // width of image sequence data
const int seq_height = 42; // height of image sequence data
const int seq_delay = 200; // delay in ms

CRGB leds[seq_width];

const int seq[42][30] PROGMEM = {{0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0},{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,5,0,0,0,0,0,0,0,0},{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},{0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,6,1,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,7,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,8,1,1,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,9,1,1,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,10,1,1,11,0,0,0,0,0,0,0,0,0,0,12,1,1},{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0},{0,0,1,1,1,13,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},{0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,1,1,1,14,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,15,0,0,0,0,0,0,0,0,0,0,1,1,0},{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1},{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1},{0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1},{0,0,0,1,1,16,0,0,0,0,0,0,0,0,0,0,0,0,17,1,1,0,0,0,0,0,0,0,0,0},{0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,18,1,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,1,1,19,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,20,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,21,0,0},{1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},{0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,22,0},{0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0},{0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,23,0,0,0,0,0,0,0,0,0,1,1,0},{0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1}};
const int pallette[24] PROGMEM = {0x000000,0xFFFFFF,0x7F7F7F,0xD0D0D0,0x3A3A3A,0xBCBCBC,0xFDFDFD,0x010101,0x3E3E3E,0xE9E9E9,0x6D6D6D,0x0E0E0E,0xF3F3F3,0x3B3B3B,0x090909,0x2A2A2A,0xFBFBFB,0x4E4E4E,0x030303,0xA3A3A3,0x151515,0x8D8D8D,0x5E5E5E,0xFEFEFE};
/* Declare the NeoPixel strip object:
*     * Argument 1 = Number of LEDs in the LED strip
*     * Argument 2 = Arduino pin number
*     * Argument 3 = LED strip color order
*
* The FastLED_NeoPixel version uses template arguments instead of function
* arguments. Note the use of '<>' brackets!
*
* You can switch between libraries by commenting out one of these two objects.
* In this example they should behave identically.
*/
// Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_GRB);  // <- Adafruit NeoPixel version

void setup() {
  delay(3000); // 3 second delay for recovery
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, seq_width);
//  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, seq_width);
  FastLED.setBrightness(BRIGHTNESS);

  blank(100);
}

void loop() {
	
  for (byte row = 0; row < seq_height; row++) {
    for (byte col= 0; col< seq_width; col++) {
      // lookup from prog mem
      int pixelBuffer = pgm_read_byte(&(seq[row][col]));
      int colorBuffer = pgm_read_byte(&(pallette[pixelBuffer]));
      leds[col] = colorBuffer;
      
    }
    FastLED.show();  
    delay(seq_delay);
	}
	blank(1000);
}





/*
* Blanks the LEDs and waits for a short time.
*/
void blank(unsigned long wait) {
	for (byte col= 0; col< seq_width; col++) {
      
      leds[col] = 0x000000;
      
    }
    FastLED.show();  
	delay(wait);
}
