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

#define LED_TYPE    WS2812B
#define COLOR_ORDER NEO_GRB + NEO_KHZ800



#define BRIGHTNESS          50


//========./assets/sunset.png======== - generated 1662472339006
 
const int seq_width = 30; // width of image sequence data
const int seq_height = 30; // height of image sequence data
const int seq_delay = 100; // delay in ms

CRGB leds[seq_width];
 
const int seq[30][30] PROGMEM = {{0,0,1,1,1,1,1,1,2,2,3,3,4,4,4,4,5,5,6,7,8,8,9,10,11,12,12,12,12,12},{0,0,0,1,1,1,1,1,1,2,2,3,3,3,4,4,4,5,5,6,7,8,9,9,10,11,12,12,12,12},{0,0,0,0,1,1,1,1,1,1,2,2,3,3,3,4,4,4,5,5,6,7,8,8,9,10,11,12,12,12},{0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,4,4,4,4,5,5,6,7,8,9,9,10,11,12,12},{13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,4,4,4,4,5,5,6,7,8,9,9,10,11,11},{13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,4,4,4,4,5,5,6,7,8,8,9,10,11},{14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,3,4,4,4,5,5,6,7,8,8,9,10},{14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,3,4,4,4,5,5,6,7,8,8,9},{15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,4,4,4,4,5,5,6,7,8,8},{16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,3,4,4,4,5,5,6,7,8},{16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,3,4,4,4,5,5,6,7},{16,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,3,4,4,4,5,5,6},{17,16,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,3,4,4,4,5,5},{17,17,16,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,3,4,4,4,5},{18,17,17,17,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,3,4,4,4},{18,18,17,17,17,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,4,4,4},{18,18,18,17,17,16,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,3,4},{18,18,18,18,17,17,16,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3,3},{19,18,18,18,18,17,17,16,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3,3},{20,19,18,18,18,18,17,17,16,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2,3},{21,20,19,18,18,18,18,17,17,17,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2,2},{21,21,20,19,18,18,18,18,17,17,16,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1,2},{22,21,21,20,19,18,18,18,18,17,17,16,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1,1},{22,22,21,21,20,19,18,18,18,18,17,17,16,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1,1},{22,22,22,21,21,20,19,18,18,18,18,17,17,16,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1,1},{22,22,22,22,21,21,20,19,18,18,18,18,17,17,17,16,16,15,14,14,13,13,0,0,0,0,0,1,1,1},{22,22,22,22,22,21,21,20,19,18,18,18,18,17,17,16,16,16,15,14,14,13,13,0,0,0,0,0,1,1},{22,22,22,22,22,22,21,21,20,19,18,18,18,18,17,17,17,16,16,15,14,14,13,13,0,0,0,0,0,1},{22,22,22,22,22,22,22,21,21,20,19,18,18,18,18,17,17,16,16,16,15,14,14,13,13,0,0,0,0,0},{22,22,22,22,22,22,22,22,21,21,20,19,18,18,18,18,17,17,16,16,16,15,14,14,13,13,0,0,0,0}};
const int pallette[23] = {0xff0066,0xff3333,0xff6633,0xff9933,0xffcc33,0xffff33,0xccff33,0xcccc33,0x99cc33,0x66cc33,0x33cc33,0x339966,0x009966,0xff0099,0xcc0099,0xcc3399,0x993399,0x663399,0x333399,0x336699,0x006699,0x0066cc,0x0099cc};
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
  FastLED.addLeds<LED_TYPE, DATA_PIN, RGB>(leds, seq_width);
//  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, seq_width);
  FastLED.setBrightness(BRIGHTNESS);

  blank(100);
}

void loop() {
	
  for (byte row = 0; row < seq_height; row++) {
    for (byte col= 0; col< seq_width; col++) {
      // lookup from prog mem
      int pixelBuffer = pgm_read_byte(&(seq[row][col]));
      int colorBuffer = pallette[pixelBuffer];
      
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
