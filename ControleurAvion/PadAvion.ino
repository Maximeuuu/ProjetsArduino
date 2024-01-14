//importations
#include "Mouse.h"
#include "Keyboard.h"


// definition des pin utilises
const int switchPin = 2;       // bouton pour allumer ou eteindre le controle du pad
//const int mouseButton = 5;   // input pin for the mouse pushButton
const int ledPin = 3;          // LED ON/OFF
const int xAxis = A0;          // axe x joystick
const int yAxis = A1;          // axe y joystick
const int button1=4;          // bouton 1
const int button2=5;          // bouton 2
const int button3=6;          // bouton 3
const int button4=7;          // bouton 4



// parametres pour lire le joystick:
int range = 12;               // output range of X or Y movement
int responseDelay = 100;        // response delay of the mouse, in ms
int threshold = range / 4;    // resting threshold
int center = range / 2;       // resting position value


bool mouseIsActive = false;    // bloquer ou non l'utilisation du pad
int lastSwitchState = LOW;        // ancien etat du bouton ON/OFF




void setup() {
  Serial.begin(9600);

  pinMode(switchPin, INPUT);       // bouton ON/OFF pin
  pinMode(ledPin, OUTPUT);         // LED pin
  pinMode(button1, INPUT);           // bouton 1
  pinMode(button2, INPUT);           // bouton 2
  pinMode(button3, INPUT);           // bouton 3
  pinMode(button4, INPUT);           // bouton 4

  Mouse.begin(); //prendre le controle de la souris
  Keyboard.begin(); //prendre le controle du clavier ?
}

void loop() {
  int switchState = digitalRead(switchPin); // etat du bouton ON/OFF
//s'il change et qu'il est HIGH alors il active le pad :
  if (switchState != lastSwitchState) {
    if (switchState == HIGH) {
      mouseIsActive = !mouseIsActive;
    }
    if (mouseIsActive) {
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


  // if the mouse control state is active, move the mouse:
  if (mouseIsActive) {
    if (xReading > 1) {
      //Serial.print("5");
      //Serial.print("\n");
      Keyboard.write(0xE5);
    }
    if (xReading < -1) {
      //Serial.print("8");
      //Serial.print("\n");
      Keyboard.write(0xE8);
    }
    if (yReading > 1) {
      //Serial.print("4");
      //Serial.print("\n");
      Keyboard.write(0xE4);
    }
    if (yReading < -1) {
      //Serial.print("6");
      //Serial.print("\n");
      Keyboard.write(0xE6);
    }
    if (digitalRead(button1) == HIGH){ // etat du bouton 1
      //Serial.print("E");
      //Serial.print("\n");
      Keyboard.write(101);
    }
    if (digitalRead(button2) == HIGH){ // etat du bouton 2
      //Serial.print("F");
      //Serial.print("\n");
      Keyboard.write(102);
    }
    if (digitalRead(button3) == HIGH){ // etat du bouton 3
      //Serial.print("G");
      //Serial.print("\n");
      Keyboard.write(103);
    }
    if (digitalRead(button4) == HIGH){ // etat du bouton 4
      //Serial.print("space");
      //Serial.print("\n");
      Keyboard.write(0x20);
    }


    /*
    autres Boutons...
    */

/*
    // read the mouse button and click or not click:
    // if the mouse button is pressed:
    if (digitalRead(mouseButton) == HIGH) {
      // if the mouse is not pressed, press it:
     if (!Mouse.isPressed(MOUSE_LEFT)) {
       Mouse.press(MOUSE_LEFT);
     }
    }
    // else the mouse button is not pressed:
   else {
     // if the mouse is pressed, release it:
     if (Mouse.isPressed(MOUSE_LEFT)) {
        Mouse.release(MOUSE_LEFT);
     }
  }
*/

  }


  delay(responseDelay);
}





/*
  reads an axis (0 or 1 for x or y) and scales the analog input range to a range
  from 0 to <range>
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
