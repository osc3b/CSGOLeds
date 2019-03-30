#include "FastLED.h"

#define NUM_LEDS 110
#define DATA_PIN 6

// Baudrate, higher rate allows faster refresh rate and more LEDs (defined in /etc/boblight.conf)
#define serialRate 1000000

// Initialise LED-array
CRGB leds[NUM_LEDS];

void setup() {
  // Use NEOPIXEL to keep true colors
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  
  // Initial RGB flash
  LEDS.showColor(CRGB(255, 0, 0));
  delay(500);
  LEDS.showColor(CRGB(0, 255, 0));
  delay(500);
  LEDS.showColor(CRGB(0, 0, 255));
  delay(500);
  LEDS.showColor(CRGB(0, 0, 0));
  
  Serial.begin(serialRate); //Comenzar la comunicación
}

void loop() {  
  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));
  // Read the transmission data and set LED values
  while(!Serial.available());
  switch(Serial.read()){
    case '1':
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(0,255,0); //Pone todos los leds a verde
    }
    // Shows new values
    FastLED.show();
    break;
    case '2':
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(255,0,0); //Pone todos los leds a rojo
    }
    FastLED.show();
    delay(1000);
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(0,0,0); //Pone todos los leds a negro
    }
    FastLED.show();
    break;
  }
}
