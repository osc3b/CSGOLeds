#include "FastLED.h"

#define NUM_LEDS 110
#define DATA_PIN 6

// Baudrate
#define serialRate 1000000

// Inicializar LED-array
CRGB leds[NUM_LEDS];
int vida = 100; //Porcentaje Vida
boolean libre; //Saber cuando esta libre
int ancho, alto; 

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
  float fAlto = NUM_LEDS/(((16.0/9)*2)+2);
  alto = round(fAlto);
  ancho = round(fAlto*(16.0/9));
  libre = true;
  Serial.print("Leds alto: "); 
  Serial.println(alto);
  Serial.print("Leds ancho: "); 
  Serial.println(ancho);
  Serial.println("Programa listo para recibir");
}

void loop() {  
  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));
  /*RECOGIDA DE DATOS*/
  //while(!Serial.available());
  int in = Serial.parseInt();
  Serial.print("He recibido: "); 
  Serial.println(in);
  switch(in){
    /* EL JUGADOR REALIZA UNA KILL */
    case 1: //KILL
    libre = false;
    Serial.println("Has matado a uno");
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(255,0,0); //Pone todos los leds a rojo
    }
    FastLED.show();
    delay(1000);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(0,0,0); //Pone todos los leds a negro
    }
    FastLED.show();
    libre = true;
    break;
    /* EL JUGADOR HA SIDO FLASHEADO */
    case 2: //FLASH
    libre = false;
    Serial.println("Flash!");
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(255,255,255); //Pone todos los leds a blanco
    }
    FastLED.show();
    delay(2000);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(0,0,0); //Pone todos los leds a negro
    }
    FastLED.show();
    libre = true;
    break;
  }
  if(in >= 500 && in <= 600){
    vida = in - 500;
    Serial.print("Vida: "); 
    Serial.println(vida);
  }
  /*MOSTRAR VIDA*/
  if(libre){
    if(vida==100){
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].setRGB(0,255,0); //Pone todos los leds a verde
      }
      FastLED.show();
    } else {
      int nLeds = round(((float)(2*alto + ancho)/100)*vida);
      Serial.println(nLeds);
      if(vida >= 75)
        mostrarNleds(nLeds, 0, 255, 0);
      else{
        if(vida >= 50)
          mostrarNleds(nLeds, 255, 255, 0);
        else{
          if(vida >= 25)
            mostrarNleds(nLeds, 255, 165, 0);
          else
            mostrarNleds(nLeds, 255, 0, 0);
        }
      }
    }
  }
}

/*Con esta linea enviamos tanto el numero de leds (n), como los colores (r,g,b)*/
void mostrarNleds(int n, int r, int g, int b){
  int fin = (2*alto + ancho) - 1;
  int inicio = fin - n;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(0,0,0); //Pone todos los leds a negro
  }
  for (int i = inicio - 1; i < fin; i++){
    leds[i].setRGB(r, g, b);
  } 
  FastLED.show();
}
