int motorStangaInainte = 3;
int motorStangaInapoi = 6;
int motorDreaptaInainte = 9;
int motorDreaptaInapoi = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorStangaInainte, OUTPUT);
  pinMode(motorStangaInapoi, OUTPUT);
  pinMode(motorDreaptaInainte, OUTPUT);
  pinMode(motorDreaptaInapoi, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  controlDirection(10, 255);
  delay(1000);
 
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
      case 10:
        // Forward
        digitalWrite(motorDreaptaInainte, HIGH);
        analogWrite(motorDreaptaInapoi, 255-100);
        digitalWrite(motorStangaInainte, HIGH);
        analogWrite(motorStangaInapoi, 255-100);
        break;
      case 2:
        // Reverse
        digitalWrite(motorDreaptaInainte, LOW);
        analogWrite(motorDreaptaInapoi, 255-s);
        digitalWrite(motorStangaInainte, LOW);
        analogWrite(motorStangaInapoi, 255-s);
        break;
      case 3:
        // Wide Right
        digitalWrite(motorDreaptaInainte, LOW);
        digitalWrite(motorDreaptaInapoi, LOW);
        digitalWrite(motorStangaInainte, HIGH);
        digitalWrite(motorStangaInapoi, LOW);
        break;
      case 4:
        // Tight Right
        digitalWrite(motorDreaptaInainte, LOW);
        digitalWrite(motorDreaptaInapoi, HIGH);
        digitalWrite(motorStangaInainte, HIGH);
        digitalWrite(motorStangaInapoi, LOW);
        break;
      case 5:
        // Wide Left
        digitalWrite(motorDreaptaInainte, HIGH);
        digitalWrite(motorDreaptaInapoi, LOW);
        digitalWrite(motorStangaInainte, LOW);
        digitalWrite(motorStangaInapoi, LOW);
        break;
      case 6:
        // Tight Left
        digitalWrite(motorDreaptaInainte, HIGH);
        digitalWrite(motorDreaptaInapoi, LOW);
        digitalWrite(motorStangaInainte, LOW);
        digitalWrite(motorStangaInapoi, HIGH);
        break;    
  }
}
