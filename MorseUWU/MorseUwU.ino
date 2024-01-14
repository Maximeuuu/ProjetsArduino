void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

   point();
   point();
   tiret();
   delay(500);
    point();
    tiret();
    tiret();
    delay(500);
    point();
    point();
    tiret();
    delay(3000);
  }

  void point(){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
  }

  void tiret(){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(750);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
  }
