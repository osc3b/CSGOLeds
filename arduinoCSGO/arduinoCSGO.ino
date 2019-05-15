#include "FastLED.h"

#define NUM_LEDS 110
#define DATA_PIN 6

// Baudrate
#define serialRate 500000

// Inicializar LED-array
CRGB leds[NUM_LEDS];
int vida = 100; //Porcentaje Vida
boolean libre = true; //Saber cuando esta libre
boolean bomba = false;
int ancho, alto; 

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  
  // Calibracion inicial
  arcoiris();
  delay(500);
   
  Serial.begin(serialRate); //Comenzar la comunicación
  Serial.setTimeout(1);
  float fAlto = NUM_LEDS/(((16.0/9)*2)+2);
  alto = round(fAlto);
  ancho = round(fAlto*(16.0/9));
  Serial.print(ancho);
  Serial.print("x"); 
  Serial.println(alto);
  Serial.println("Programa listo para recibir");
  libre = true;
  mostrarVida();
}

void loop() {  
  //memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));
 
  /*RECOGIDA DE DATOS*/
  while(!Serial.available());
  int in = Serial.parseInt();
  Serial.print("He recibido: "); 
  Serial.println(in);
  
  /* CAMBIO DE VIDA */
  if(in >= 500 && in <= 600){
    vida = in - 500;
    Serial.print("Vida: "); 
    Serial.println(vida);
    mostrarVida();
  }
  
  /* EVENTOS */
  if(libre){
    switch(in){
      
      /* EL JUGADOR REALIZA UNA KILL */
      case 1: //KILL
      libre = false;
      //Serial.println("Has matado a uno");
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].setRGB(255,0,0); //Pone todos los leds a rojo
      }
      FastLED.show();
      delay(1000);
      libre = true;
      mostrarVida();
      break;
      
      /* BOMBA COLOCADA */
      case 5: //BOMBA
      bomba = true;
      mostrarVida();
      break;
      
      /* BOMBA EXPLOTA */
      case 6: //
      libre = false;
      randomleds(255,0,0);
      libre = true;
      bomba = false;
      mostrarVida();
      break;
      
      /* BOMBA DESACTIVA */
      case 7: //
      libre = false;
      randomleds(0,200,255);
      libre = true;
      bomba = false;
      mostrarVida();
      break;
      
      /* EL JUGADOR HA SIDO FLASHEADO */
      case 2: //FLASH
      libre = false;
      //Serial.println("Flash!");
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].setRGB(255,255,255); //Pone todos los leds a blanco
      }
      FastLED.show();
      delay(2000);
      libre = true;
      mostrarVida();
      break;
      
      /*RONDA GANADA Y PERDIDA*/
      case 3: //GANADA
      libre = false;
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].setRGB(255,255,0); //Pone todos los leds a amarillo, paulativamente
        FastLED.show();
        delay(5);
      }
      delay(1000);
      for (int i = NUM_LEDS-1; i >= 0; i--) {
        leds[i].setRGB(0,0,0); //Pone todos los leds a negro, paulativamente
        FastLED.show();
        delay(5);
      }
      libre = true;
      bomba = false;
      mostrarVida();
      break;
      
      /* RONDA PERDIDA */
      case 4: //PERDIDA
      libre = false;
      int j = (2*alto + ancho)/2;
      for (int i = (2*alto + ancho)/2; i < 2*alto + ancho && j >=0; i++) {
        leds[i].setRGB(255,0,0); //Pone la mitad de allos led en rojo
        leds[j].setRGB(255,0,0);
        FastLED.show();
        delay(10);
        j--;
      }
      j = (2*alto + ancho)/2;
      for (int i = (2*alto + ancho)/2; i < 2*alto + ancho && j >=0; i++) {
        leds[i].setRGB(0,0,0); //Pone la mitad de allos led en rojo
        leds[j].setRGB(0,0,0);
        FastLED.show();
        delay(10);
        j--;
      }
      delay(2000);
      libre = true;
      bomba = false;
      mostrarVida();
      break;
    }
  }
}

/*MOSTRAR VIDA*/
void mostrarVida(){
  if(libre){
    if(bomba){
      for (int i = 2*alto + ancho + 1; i < NUM_LEDS; i++) {
        leds[i].setRGB(255,0,0); //Pone todos los leds a rojo
      }
      FastLED.show();
    }
    if(vida==100){
      mostrarNleds(2*alto + ancho, 0, 255, 0);
    } else {
      int nLeds = round(((float)(2*alto + ancho)/100)*vida);
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

/*RELLENA LOS LEDS DE FORMA ALEATORIA*/
void randomleds(int r, int g, int b){
  //CREAAMOS UN ARRAY CON LOS NUMEROS
  int numeros[NUM_LEDS]; 
  for (int i = 0; i < NUM_LEDS; i++) numeros[i] = i;

  for (int i = 0; i < NUM_LEDS; i++) {
    int j = random(i, NUM_LEDS);

    //INTERCAMBIAMOS x[i] and x[j]
    int t = numeros[i];
    numeros[i] = numeros[j];
    numeros[j] = t;
  }

  for (int i = 0; i < NUM_LEDS; i++) {     
    leds[numeros[i]].setRGB(r,g,b);
    FastLED.show();
    delay(25);
  }
  for (int i = NUM_LEDS-1; i >= 0; i--) {
    leds[i].setRGB(0,0,0); //Pone todos los leds a negro, paulativamente
    FastLED.show();
    delay(5);
  }
}

/*ARCOIRIS*/
void arcoiris(){
  int r = 255, g = 0, b = 0, cont = 0;
  for(int i=0; i < NUM_LEDS; i++){
    leds[i].setRGB(r,g,b);
    FastLED.show();
    delay(10);
    cont = round(1275.0/NUM_LEDS + cont);
    if(cont <= 255)
      g = cont;
    else{
      if(cont <= 510)
        r = 510 - cont;
      else{
        if(cont <= 765)
          b = cont - 510;
        else{
          if(cont <= 1020)
            g = 1020 - cont;
          else
            r = cont - 1020;
        }
      }
    }
  }
  delay(500);
  for(int i = NUM_LEDS-1; i >= 0; i--){
    leds[i].setRGB(0,0,0);
    FastLED.show();
    delay(10);
  }
}

/*Con esta linea enviamos tanto el numero de leds (n), como los colores (r,g,b)*/
void mostrarNleds(int n, int r, int g, int b){
  int fin = (2*alto + ancho);
  int inicio = 1;
  if(fin > n)
    inicio = fin - n;
  for (int i = 0; i < fin; i++) {
    leds[i].setRGB(0,0,0); //Pone los leds a negro
  }
  for (int i = inicio - 1; i < fin; i++){
    leds[i].setRGB(r, g, b);
  } 
  FastLED.show();
}
