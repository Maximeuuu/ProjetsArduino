//importations
#include "Mouse.h"
#include "Keyboard.h"


// definition des pin utilises
const int switchPin = 2;       // bouton pour allumer ou eteindre le controle du pad
const int ledPin = 3;          // LED ON/OFF
const int xAxis = A0;          // axe x joystick
const int yAxis = A1;          // axe y joystick
const int button1=4;          // bouton 1
const int button2=5;          // bouton 2
const int button3=6;          // bouton 3
const int button4=7;          // bouton 4
const int potentiometer=A2;   // potentiometre
const int ledPin2 = 8;        // LED potentiometre
const int ledPin3 =9;         // LED potentiometre


// parametres pour lire le joystick:
int range = 12;               // output range of X or Y movement
int responseDelay = 100; //0.1        // response delay of the mouse, in ms
int threshold = range / 4;    // resting threshold
int center = range / 2;       // resting position value


bool controllerIsActive = false;    // bloquer ou non l'utilisation du pad
int lastSwitchState = LOW;        // ancien etat du bouton ON/OFF


void setup() {
  Serial.begin(9600);

  pinMode(switchPin, INPUT);       // bouton ON/OFF pin
  pinMode(ledPin, OUTPUT);         // LED pin
  pinMode(button1, INPUT);           // bouton 1
  pinMode(button2, INPUT);           // bouton 2
  pinMode(button3, INPUT);           // bouton 3
  pinMode(button4, INPUT);           // bouton 4
  pinMode(ledPin2, OUTPUT);          // LED pin 2
  pinMode(ledPin3, OUTPUT);           //LED pin 3

  Mouse.begin(); //prendre le controle de la souris
  Keyboard.begin(); //prendre le controle du clavier ?
}


void loop() {
  int switchState = digitalRead(switchPin); // etat du bouton ON/OFF
//s'il change et qu'il est HIGH alors il active le pad :
  if (switchState != lastSwitchState) {
    if (switchState == HIGH) {
      controllerIsActive = !controllerIsActive;
    }
    if (controllerIsActive) {
      digitalWrite(ledPin, HIGH);
    }
    else {
      digitalWrite(ledPin, LOW);
    }
  }
  // enregistre l'etat precedent pour la comparaison:
  lastSwitchState = switchState;


  // read and scale the two axes:
  int xReading = readAxis(A0);
  int yReading = readAxis(A1);


  // si le controlleur est active, les touches peuvent etre detectees :
  if (controllerIsActive) {
    if (xReading > 1) {
      Keyboard.write(0xE5); //5
    }
    else if (xReading < -1) {
      Keyboard.write(0xE8); //8
    }
    if (yReading > 1) {
      Keyboard.write(0xE4); //4
    }
    else if (yReading < -1) {
      Keyboard.write(0xE6); //6
    }
    if (digitalRead(button1) == HIGH){ // etat du bouton 1
      Keyboard.write(101); //E
    }
    if (digitalRead(button2) == HIGH){ // etat du bouton 2
      Keyboard.write(102); //F
    }
    if (digitalRead(button3) == HIGH){ // etat du bouton 3
      Keyboard.write(103); //G
    }
    if (digitalRead(button4) == HIGH){ // etat du bouton 4
      Keyboard.write(0x20); //space
    }

    /*
    autres Boutons...
    */
  }

  //lecture du potentiometre :
  int time = analogRead(potentiometer);
  if (time<240){
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    responseDelay = 200;
  }
  else if (time>700){
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
    responseDelay = 1;
  }
  else {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    responseDelay = 20;
  }


  delay(responseDelay);
}



//fonctions

/*
  reads an axis (0 or 1 for x or y) and scales the analog input range to a range from 0 to <range>
*/

int readAxis(int thisAxis) {
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the rest position threshold, use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  }

  // return the distance for this axis:
  return distance;
}
