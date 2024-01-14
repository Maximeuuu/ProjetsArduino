#include <Keyboard.h>

const int boutonA = 9;

void setup() {
  pinMode(boutonA, INPUT);
  Keyboard.begin();
}

void loop() {
  if(digitalRead(boutonA))
  {
    Keyboard.press('a');
    delay(100);
    Keyboard.releaseAll();
    delay(100);
  }
}
