# 1 "c:\\Users\\Roshan Yadav\\Documents\\Arduino\\Testing_Play_Ground\\Testing_Play_Ground.ino"
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
# 1 "c:\\Users\\Roshan Yadav\\Documents\\Arduino\\Testing_Play_Ground\\Demo0.ino"

int buttonPin = 3;

void setup()
{
    Serial.begin(9600);
    pinMode(buttonPin, 0x0);
}

void loop()
{
    // ...
}
# 1 "c:\\Users\\Roshan Yadav\\Documents\\Arduino\\Testing_Play_Ground\\Demo1.ino"


// setup initializes serial and the button pin

void setup()
{
    // initialize digital pin 13 as an output.
    pinMode(13, 0x1);
}

void loop()
{
    digitalWrite(13, 0x1); // turn the LED on 
    delay(1000); // wait for 1 second
    digitalWrite(13, 0x0); // turn the LED off
    delay(1000); // wait for 1 second
}
