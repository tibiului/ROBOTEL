int motorStangaInainte = 3;
int motorStangaInapoi = 6;
int motorDreaptaInainte = 9;
int motorDreaptaInapoi = 5;
int senzor1 = 2;
int senzor2 = 7;
int senzor3 = 8;
int senzor4 = 4;
int senzor5 = 10;
int senzorButon = 11;
int senzorNear = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorStangaInainte, OUTPUT);
  pinMode(motorStangaInapoi, OUTPUT);
  pinMode(motorDreaptaInainte, OUTPUT);
  pinMode(motorDreaptaInapoi, OUTPUT);
  pinMode(senzor1, INPUT);
  pinMode(senzor2, INPUT);
  pinMode(senzor3, INPUT);
  pinMode(senzor4, INPUT);
  pinMode(senzor5, INPUT);
  pinMode(senzorButon, INPUT);
  pinMode(senzorNear, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(senzor1)) {
    controlDirection(5, 255);
  } 
  if (digitalRead(senzor2)) {
    controlDirection(5, 255);
  } 
  if (digitalRead(senzor3)) {
    controlDirection(2, 255);
  } 
  if (digitalRead(senzor4)) {
    controlDirection(7, 255);
  } 
  if (digitalRead(senzor5)) {
    controlDirection(7, 255);
  } 
  if (digitalRead(senzorButon)) {
    controlDirection(0, 255);
  } 
  if (digitalRead(senzorNear)) {
    controlDirection(3, 255);
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
