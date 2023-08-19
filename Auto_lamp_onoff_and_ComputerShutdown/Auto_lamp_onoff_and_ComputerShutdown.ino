#include <IRremote.h>

#define IR_RECEIVE_PIN 9
const int ldrPin = A0;
const int micPin = A1;
const int RledPin = 5;
const int GledPin = 6;
const int BledPin = 7;
const int relayPin = 8;
int micstatus = 0;
int Irremote = 0;


void setup ()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode (RledPin, OUTPUT) ;
  pinMode (GledPin, OUTPUT) ;
  pinMode (BledPin, OUTPUT) ;
  pinMode (micPin, INPUT) ;
  pinMode(ldrPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
}
void loop ()
{
  int ldrValue = analogRead (ldrPin) ;
  int micValue = analogRead (micPin) ;
  if (micValue < 450) {
    micstatus = 1;
  }
  else {
    micstatus = 0;
  }
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    Irremote = IrReceiver.decodedIRData.command;
  } else {
    Irremote = 404;
  }


  //  delay(1000);

  // ------------------------ Operation on MIc value ------------------------
  if (micValue < 450)
  {
    digitalWrite(RledPin, HIGH);
    
  }
  else
  {
    digitalWrite(RledPin, LOW);
  }
  // ------------------------ Operation on Ldr value ------------------------
  if (ldrValue >= 500) {
    digitalWrite(GledPin, HIGH);
    digitalWrite(relayPin, LOW);

  } else {
    digitalWrite(GledPin, LOW);
    digitalWrite(relayPin, HIGH);
  }
  String newdata = "{\"Mic\": " + String(micValue) + ", \"Ldr\":" + String(ldrValue) + ", \"MicStatus\":" + String(micstatus) + ", \"IRremote\":" + String(Irremote) + "}";
  Serial.println(newdata);
}
