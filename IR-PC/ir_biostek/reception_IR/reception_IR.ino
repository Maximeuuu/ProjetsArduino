#include <IRremote.h>

//definition des pins
const int RECV_PIN  = 2;
const int RED_PIN   = 7;
const int GREEN_PIN = 8;
const int BLUE_PIN  = 9;

//contantes
const int DELAY_TIME = 250;

//variables
int redValue;
int greenValue;
int blueValue;
String serial_input;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop()
{
  delay(DELAY_TIME);

  if (irrecv.decode(&results))
  {
    unsigned long value = results.value;
    Serial.println(value, HEX);
    delay(DELAY_TIME);
    
    irrecv.resume();
  }

  if (Serial.available() > 0)
  {
    serial_input = Serial.readStringUntil('\n');
    serial_input.trim(); // Supprime les espaces indésirables
    
    // Extraction des valeurs RGB
    sscanf(serial_input.c_str(), "%d,%d,%d", &redValue, &greenValue, &blueValue);
    
    analogWrite(RED_PIN, redValue);
    analogWrite(GREEN_PIN, greenValue);
    analogWrite(BLUE_PIN, blueValue);
  }

}
