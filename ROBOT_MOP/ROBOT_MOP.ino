#include <FastLED.h>             //  LIBRARIE PT. BARA DE NEOPIXELI
#define LED_PIN 2                //  DEFINIM PINUL PRIN CARE BARA DE NEOPIXELI COMUNICA CU ARDUINO
#define NUM_LEDS 8               //  DEFINIM NUMARUL DE LEDURI DE PE BARA DE NEOPIXELI
#include<Servo.h>                //  LIBRARIE PT. SERVOMOTOR 
#include "SENZOR_ULTRASONIC.h"   //  LIBRARIE PT. SENZORUL ULTRASONIC
#include <LiquidCrystal_I2C.h>   //  LIBRARIE PT. I2C

LiquidCrystal_I2C lcd(0x3F,16,2); //  SETARE LCD DISPLAY PENTRU 16 CARACTERE SI DOUA LINII
CRGB leds[NUM_LEDS];              //  FOLOSIM FUNCTIA PT. BARA DE NEOPIXELI
Servo motoras;                    //  FOLOSIM SERVOMOTORUL


int motorStangaInainte = 3;      //  FOLOSIM PINUL PWM 3 PENTRU MOTOR
int motorStangaInapoi = 6;       //  FOLOSIM PINUL PWM 6 PENTRU MOTOR
int motorDreaptaInainte = 9;     //  FOLOSIM PINUL PWM 9 PENTRU MOTOR
int motorDreaptaInapoi = 5;      //  FOLOSIM PINUL PWM 5 PENTRU MOTOR
int trig = 8;                    //  PIN TRIG PENTRU SENZOR ULTRASUNETE
int echo = 12;                   //  PIN ECHO PENTRU SENZOR ULTRASUNETE

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

  lcd.init();                                             //  INITIALIZEAZA LCD-UL
  lcd.backlight();                                        //  SETEAZA LUMINA DIN SPATE
  byte inainte[] = {
      B00100,
      B01110,
      B11111,
      B00100,
      B00100,
      B00100,
      B00100,
      B00100
  };
  byte oprit[] = {
      B11111,
      B11111,
      B11111,
      B11111,
      B00100,
      B00100,
      B00100,
      B00100
  };
  lcd.createChar(0, inainte);
  lcd.createChar(1, oprit); 
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
    lcdInainte();   
    delay(200);
  }
  if (distantaInainte < 30) {
    controlDirection(3, 255);
    for (int i = 0; i < 8; i++) {
      leds[i] = CRGB(25, 0, 0);
      FastLED.show();
    }
    lcdInainte();    
    delay(50);
  }
  
  distantaInainte = verificaDistanta();

  if (distantaInainte < 20) {
    controlDirection(0, 255);
    for (int i = 0; i < 8; i++) {   
      leds[i] = CRGB(255, 255, 0);
      FastLED.show();
    }  
    lcdStop();  
    delay(10);
    controlDirection(4, 255);
    delay(10);    
    controlDirection(0, 255);  
    delay(10);                   
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
        controlDirection(4, 255);
        delay(100);    
        controlDirection(5, 255);
        for(int i = 0; i < 8; i++) {
          leds[i] = CRGB(255, 255, 255);
          FastLED.show();    
        }    
        lcdDreapta();  
        delay(100);
      } else if (distantaDreapta < distantaStanga) {
          controlDirection(4, 255);
          delay(100);    
          controlDirection(7, 255);
          for(int i = 0; i < 8; i++) {
            leds[i] = CRGB(255, 0, 25);
            FastLED.show();    
          }  
          lcdStanga();    
          delay(100);
        } else if ((distantaDreapta < 20) || (distantaStanga < 20)) {
            controlDirection(0, 255);  
            delay(100);                  
            controlDirection(4, 255);
            delay(300);
          } else {
             controlDirection(2, 255);
             delay(200);
            }
  } else {
       controlDirection(2, 255);
       delay(100);
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
        analogWrite(motorDreaptaInapoi, 255-100);
        digitalWrite(motorStangaInainte, HIGH);
        analogWrite(motorStangaInapoi, 255-100);
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

void lcdDreapta() {
    lcd.setCursor(0,0);
    lcd.print("--------------->");
    lcd.setCursor(0,1);
    lcd.print("----DREAPTA---->");
}
void lcdStanga() {
    lcd.setCursor(0,0);
    lcd.print("<---------------");
    lcd.setCursor(0,1);
    lcd.print("<----STANGA-----");;
}
void lcdInainte() {
    lcd.begin(16, 2);
    lcd.home();
    lcd.write(0);
    lcd.setCursor(6,0);
    lcd.print("MERGE");
    lcd.setCursor(15,0);
    lcd.write(0);
    lcd.setCursor(1,1);
    lcd.write(0);
    lcd.setCursor(5,1);
    lcd.print("INAINTE");
    lcd.setCursor(14,1);
    lcd.write(0);
}
void lcdStop() {
    lcd.setCursor(0,0);
    lcd.print("      STOP      ");
    lcd.setCursor(0,1);
    for(int i = 0; i < 16; i++) {
    lcd.write(1);
    }
}    
void lcdInapoi() {
    lcd.setCursor(0,0);
    lcd.print("     INAPOI     ");
    lcd.setCursor(0,1);
    lcd.print("                ");   
}    
