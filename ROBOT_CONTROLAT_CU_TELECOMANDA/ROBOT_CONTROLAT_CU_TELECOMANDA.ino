#include <IRremote.h> // LIBRARIE PT. SENZOR INFRAROSU 
int pinIR = 13;
IRrecv irrecv(pinIR); // SE INITIALIZEAZA LIBRARIA
decode_results results;  //  SE PRIMESC REZULTATELE IN results
int motorStangaInainte = 3;      //  FOLOSIM PINUL PWM 3 PENTRU MOTOR
int motorStangaInapoi = 6;       //  FOLOSIM PINUL PWM 6 PENTRU MOTOR
int motorDreaptaInainte = 9;     //  FOLOSIM PINUL PWM 9 PENTRU MOTOR
int motorDreaptaInapoi = 5;      //  FOLOSIM PINUL PWM 5 PENTRU MOTOR
//unsigned long int inainte = ;
//unsigned long int inapoi = ;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

}

void loop() {
  
 if(irrecv.decode(&results)) { //  senzorul primeste date
      Serial.print("cod IRL");
  Serial.print(results.value, HEX); //AFISARE COD IR , IN HEXA
  Serial.println("");
  Serial.print(results.bits);
  Serial.println("");
  Serial.print(results.value, BIN); 
  Serial.println("");
  Serial.print(results.value);  // DECIMAL
  Serial.println("");
      irrecv.resume();  // sterge din memorie
    }

if(irrecv.decode( &results ) )  {  
  unsigned long int codIr = results.value;
    if( codIr == 924466310 )  { 
        controlDirection(2, 255);
    }  
    if( codIr == 2737486129 )  { 
        controlDirection(4, 255);
    }
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
