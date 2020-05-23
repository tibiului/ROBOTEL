#include <FastLED.h>  //  LIBRARIE PT. BARA DE NEOPIXELI
#define LED_PIN 2     //  DEFINIM PINUL PRIN CARE BARA DE NEOPIXELI COMUNICA CU ARDUINO
#define NUM_LEDS 8    //  DEFINIM NUMARUL DE LEDURI DE PE BARA DE NEOPIXELI
#include<Servo.h>     //  LIBRARIE PENTRU SERVOMOTOR 
#include "SENZOR_ULTRASONIC.h"



CRGB leds[NUM_LEDS];  //  FOLOSIM FUNCTIA PT. BARA DE NEOPIXELI
Servo motoras;        //  FOLOSIM SERVOMOTORUL


int motorStangaInainte = 3;
int motorStangaInapoi = 6;
int motorDreaptaInainte = 9;
int motorDreaptaInapoi = 5;
int trig = 8;                  //  PIN TRIG PENTRU SENZOR ULTRASUNETE
int echo = 12;                  //  PIN ECHO PENTRU SENZOR ULTRASUNETE

float distantaStanga = 0;
float distantaDreapta = 0;
float distantaInainte = 0;
long durata;
float distanta;

void setup() {
  pinMode(motorStangaInainte, OUTPUT);
  pinMode(motorStangaInapoi, OUTPUT);
  pinMode(motorDreaptaInainte, OUTPUT);
  pinMode(motorDreaptaInapoi, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);  //  BARA DE NEOPIXELI
  motoras.attach(10);                                     //  FOLOSIM PINUL PWM 10 PENTRU SERVOMOTOR 
}

void loop() {
  motoras.write(90);  // initializam pozitia servomotorului la 90 in fata (merge pana la 180)
  delay(200);
  distantaInainte = verificaDistanta();
  if(distantaInainte > 100) {     
    controlDirection(2, 255);
    for(int i = 0; i < 8; i++) {
      leds[i] = CRGB(255,0,0);
      FastLED.show();    
    }      
    delay(200);
  }
  if (distantaInainte < 50) {
    controlDirection(3, 255);
    for (int i = 0; i < 8; i++) {
      leds[i] = CRGB(25, 0, 0);
      FastLED.show();
    }     
    delay(200);
  }
  if (distantaInainte < 20) {
    controlDirection(0, 255);
    for (int i = 0; i < 8; i++) {   // Stinge toate LED-urile
      leds[i] = CRGB(255, 255, 0);
      FastLED.show();
    }        
    delay(200);
    controlDirection(4, 255);
    delay(150);    
    controlDirection(0, 255);  
    delay(100);                   
    motoras.write(0);          
    delay(300); 
    distantaDreapta = verificaDistanta();
    delay(300);
    motoras.write(180);          
    delay(300);
    distantaStanga = verificaDistanta();
    delay(300);
    motoras.write(90);          
    delay(200);
      if (distantaDreapta > distantaStanga) {
        controlDirection(5, 255);
        for(int i = 0; i < 8; i++) {
         leds[i] = CRGB(255,255,255);
          FastLED.show();    
        }      
    delay(200);
        delay(200);
      } else if (distantaDreapta < distantaStanga) {
          controlDirection(7, 255);
          for(int i = 0; i < 8; i++) {
            leds[i] = CRGB(255,0,25);
            FastLED.show();    
          }      
          delay(200);
        } else if ((distantaDreapta < 20) || (distantaStanga < 20)) {
            controlDirection(4, 255);
            delay(200);
          } else {
             controlDirection(2, 255);
             delay(200);
            }
  } else {
       controlDirection(2, 255);
       delay(200);
    }        
}
 
void controlDirection( int d , int s ) { 
  switch( d ) {
      case 0:
        // STOP Normal
        digitalWrite(motorDreaptaInainte, LOW);
        digitalWrite(motorDreaptaInapoi, LOW);
        digitalWrite(motorStangaInainte, LOW);
        digitalWrite(motorStangaInapoi, LOW);
        break;
      case 1:
        // STOP Fast
        digitalWrite(motorDreaptaInainte, HIGH);
        digitalWrite(motorDreaptaInapoi, HIGH);
        digitalWrite(motorStangaInainte, HIGH);
        digitalWrite(motorStangaInapoi, HIGH);
        break;
      case 2:
        // Forward
        digitalWrite(motorDreaptaInainte, HIGH);
        digitalWrite(motorDreaptaInapoi, LOW);
        digitalWrite(motorStangaInainte, HIGH);
        digitalWrite(motorStangaInapoi, LOW);
        break;
      case 3:
        // SLOW Forward
        digitalWrite(motorDreaptaInainte, HIGH);
        analogWrite(motorDreaptaInapoi, 255-150);
        digitalWrite(motorStangaInainte, HIGH);
        analogWrite(motorStangaInapoi, 255-150);
        break;        
      case 4:
        // Reverse
        digitalWrite(motorDreaptaInainte, LOW);
        digitalWrite(motorDreaptaInapoi, HIGH);
        digitalWrite(motorStangaInainte, LOW);
        digitalWrite(motorStangaInapoi, HIGH);
        break;
      case 5:
        // Wide Right
        digitalWrite(motorDreaptaInainte, LOW);
        digitalWrite(motorDreaptaInapoi, LOW);
        digitalWrite(motorStangaInainte, HIGH);
        digitalWrite(motorStangaInapoi, LOW);
        break;
      case 6:
        // Tight Right
        digitalWrite(motorDreaptaInainte, LOW);
        digitalWrite(motorDreaptaInapoi, HIGH);
        digitalWrite(motorStangaInainte, HIGH);
        digitalWrite(motorStangaInapoi, LOW);
        break;
      case 7:
        // Wide Left
        digitalWrite(motorDreaptaInainte, HIGH);
        digitalWrite(motorDreaptaInapoi, LOW);
        digitalWrite(motorStangaInainte, LOW);
        digitalWrite(motorStangaInapoi, LOW);                      
        break;
      case 8:
        // Tight Left
        digitalWrite(motorDreaptaInainte, HIGH);
        digitalWrite(motorDreaptaInapoi, LOW);
        digitalWrite(motorStangaInainte, LOW);
        digitalWrite(motorStangaInapoi, HIGH);                        
        break;    
  }
}

int verificaDistanta() {
  
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  durata = pulseIn (echo ,HIGH);
  distanta = (durata * 0.0342) / 2; //transformare in cm
  return distanta;
} 

void motorTest() {  //  //motorTest();
 
  controlDirection(0, 255); //  STOP NORMAL
  delay(5000); 
  controlDirection(2, 255); //  STOP FAST
  delay(5000);
  controlDirection(3, 255); //  SLOW FORWARD
  delay(5000); 
  for (int i = 0; i < 8; i++) {   // Stinge toate LED-uril
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();              
  }
  controlDirection(4, 255); //  REVERSE
  delay(5000);
  controlDirection(5, 255); //  WIDE RIGHT
  delay(5000);
  controlDirection(6, 255); //  TIGHT RIGHT
  delay(5000);
  controlDirection(7, 255); //  WIDE LEFT
  delay(5000); 
  controlDirection(8, 255); //  TIGHT LEFT
  delay(5000); 
  controlDirection(1, 255); //  STOP FAST
  delay(5000); 
}
