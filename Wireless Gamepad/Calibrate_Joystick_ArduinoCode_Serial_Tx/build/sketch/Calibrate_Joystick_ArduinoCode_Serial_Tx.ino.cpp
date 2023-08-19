#include <Arduino.h>
#line 1 "c:\\Users\\Roshan Yadav\\Documents\\Arduino\\Wireless Gamepad\\Calibrate_Joystick_ArduinoCode_Serial_Tx\\Calibrate_Joystick_ArduinoCode_Serial_Tx.ino"
int VRx = A0;

int VRy = A1;
int SW = 2;

int down_b =3;
int right_b =4;
int up_b =5;
int left_b =6;

String previousdata;
String newdata;
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int btn_up=0;
int btn_down=0;
int btn_left=0;
int btn_right=0;

#line 21 "c:\\Users\\Roshan Yadav\\Documents\\Arduino\\Wireless Gamepad\\Calibrate_Joystick_ArduinoCode_Serial_Tx\\Calibrate_Joystick_ArduinoCode_Serial_Tx.ino"
void setup();
#line 34 "c:\\Users\\Roshan Yadav\\Documents\\Arduino\\Wireless Gamepad\\Calibrate_Joystick_ArduinoCode_Serial_Tx\\Calibrate_Joystick_ArduinoCode_Serial_Tx.ino"
void loop();
#line 21 "c:\\Users\\Roshan Yadav\\Documents\\Arduino\\Wireless Gamepad\\Calibrate_Joystick_ArduinoCode_Serial_Tx\\Calibrate_Joystick_ArduinoCode_Serial_Tx.ino"
void setup() {
  Serial.begin(9600);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(down_b, INPUT_PULLUP);
  pinMode(right_b, INPUT_PULLUP);
  pinMode(left_b, INPUT_PULLUP);
  pinMode(up_b, INPUT_PULLUP);

}

void loop() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  btn_up =!digitalRead(up_b);
  btn_down=!digitalRead(down_b);
  btn_left=!digitalRead(left_b);
  btn_right=!digitalRead(right_b);
  //  mapX = map(xPosition, 0, 1023, -512, 512);
  //  mapY = map(yPosition, 0, 1023, -512, 512);
//
//    Serial.print("X: ");
//    Serial.print(xPosition);
//    Serial.print(" | Y: ");
//    Serial.print(yPosition);
//    Serial.print(" | Button: ");
//    Serial.println(SW_state);

  int j_forward = 0;
  int j_backward = 0;
  int j_left = 0;
  int j_right = 0;

  if (xPosition > 10) {
    j_forward = 1; // Back

  }
  else if (SW_state == LOW) {
    j_backward = 1;; // Switch

  }
  if (yPosition > 900) {
    j_right = 1; //Left

  }
  else if (yPosition < 100) {
    j_left = 1; //Right

  }
  if (j_forward || j_backward || j_left || j_right || btn_up || btn_down || btn_left || btn_right ) {
     newdata = "{\"forward\": " + String(j_forward) + ", \"backward\":" + String(j_backward) + ", \"left\":" + String(j_left) + ", \"right\":" + String(j_right) +", \"up_b\":" + String(btn_up)+", \"down_b\":" + String(btn_down)+", \"left_b\":" + String(btn_left)+", \"right_b\":" + String(btn_right)+"}";

  } else {
          newdata = "{\"forward\": " + String(0) + ", \"backward\":" + String(0) + ", \"left\":" + String(0) + ", \"right\":" + String(0) +", \"up_b\":" + String(0)+", \"down_b\":" + String(0)+", \"left_b\":" + String(0)+", \"right_b\":" + String(0)+"}";

  }
  if(previousdata != newdata){
    Serial.println(newdata);
    previousdata=newdata;
    }
    delay(200);
}

