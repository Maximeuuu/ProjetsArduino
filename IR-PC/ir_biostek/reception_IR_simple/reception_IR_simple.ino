#include <IRremote.h>

//definition des pins
const int RECV_PIN  = 2;

//contantes
const int DELAY_TIME = 100;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop()
{
  if (irrecv.decode(&results))
  {
    unsigned long value = results.value;
    Serial.println(value, HEX);
    delay(DELAY_TIME);

    irrecv.resume();
  }
}
