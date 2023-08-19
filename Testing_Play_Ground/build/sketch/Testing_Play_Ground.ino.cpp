#include <Arduino.h>
#line 1 "c:\\Users\\Roshan Yadav\\Documents\\Arduino\\Testing_Play_Ground\\Testing_Play_Ground.ino"
#line 1 "c:\\Users\\Roshan Yadav\\Documents\\Arduino\\Testing_Play_Ground\\Testing_Play_Ground.ino"
void setup();
#line 6 "c:\\Users\\Roshan Yadav\\Documents\\Arduino\\Testing_Play_Ground\\Testing_Play_Ground.ino"
void loop();
#line 1 "c:\\Users\\Roshan Yadav\\Documents\\Arduino\\Testing_Play_Ground\\Testing_Play_Ground.ino"
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

#line 1 "c:\\Users\\Roshan Yadav\\Documents\\Arduino\\Testing_Play_Ground\\Demo0.ino"

int buttonPin = 3;

void setup()
{
    Serial.begin(9600);
    pinMode(buttonPin, INPUT);
}

void loop()
{
    // ...
}
#line 1 "c:\\Users\\Roshan Yadav\\Documents\\Arduino\\Testing_Play_Ground\\Demo1.ino"


// setup initializes serial and the button pin

void setup()
{
    // initialize digital pin 13 as an output.
    pinMode(13, OUTPUT);
}

void loop()
{
    digitalWrite(13, HIGH); // turn the LED on 
    delay(1000);                     // wait for 1 second
    digitalWrite(13, LOW);  // turn the LED off
    delay(1000);                     // wait for 1 second
}
