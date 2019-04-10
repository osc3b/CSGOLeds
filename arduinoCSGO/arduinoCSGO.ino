#include "FastLED.h"

#define NUM_LEDS 110
#define DATA_PIN 6

// Baudrate
#define serialRate 1000000

// Inicializar LED-array
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  
  // Flash RGB inicial
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
  while(!Serial.available());
  int in = Serial.read();
  switch(in){
    case '1':
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(0,255,0); //Pone todos los leds a verde
    }
    // Mostrar en LEDs
    FastLED.show();
    break;
    case '2':
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(255,0,0); //Pone todos los leds a rojo
    }
    FastLED.show();
    delay(1000);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(0,0,0); //Pone todos los leds a negro
    }
    FastLED.show();
    break;
  }
  if(in >= 500 && in <= 600){
    int vida = in - 500;
  }
}
