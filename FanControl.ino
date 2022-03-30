#include "DHT.h"

// init vars
int upButton   = 10;
int downButton = 11;
int led1       = 4;
int led2       = 5;
int led3       = 6;
int led4       = 7;
int led5       = 8;
int fanPWM     = 9;
int fanSpeed   = 1;


void setup() {
  // Set PinModes (2-9)
  TCCR1B = TCCR1B & 0b11111000 | 0x01; // Set Timer1 (Pin 9 and 10) to 31300Hz
  pinMode(upButton,   INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(led1,        OUTPUT);
  pinMode(led2,        OUTPUT);
  pinMode(led3,        OUTPUT);
  pinMode(led4,        OUTPUT);
  pinMode(led5,        OUTPUT);
  pinMode(fanPWM,      OUTPUT);

  //Serial.begin(9600);
}

void loop() {
  // Buttonwork
  if (!digitalRead(upButton)) {
    fanSpeed++;
    delay(300);
  }
  if (!digitalRead(downButton)) {
    fanSpeed--;
    delay(300);
  }
  if (fanSpeed>5)  fanSpeed = 5;
  if (fanSpeed<0)  fanSpeed = 0;

  //Serial.println(fanSpeed);
  
  // Ledwork
  if (fanSpeed >= 1) digitalWrite(led1, HIGH);
  else digitalWrite(led1, LOW);
  if (fanSpeed >= 2) digitalWrite(led2, HIGH);
  else digitalWrite(led2, LOW);
  if (fanSpeed >= 3) digitalWrite(led3, HIGH);
  else digitalWrite(led3, LOW);
  if (fanSpeed >= 4) digitalWrite(led4, HIGH);
  else digitalWrite(led4, LOW);
  if (fanSpeed >= 5) digitalWrite(led5, HIGH);
  else digitalWrite(led5, LOW);

  // Send new Speed as PWM to Fan
  analogWrite(fanPWM, (fanSpeed*50));
}
