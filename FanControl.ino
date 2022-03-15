#include "DHT.h"

// init vars
int upButton   = 2;
int downButton = 3;
int led1       = 4;
int led2       = 5;
int led3       = 6;
int led4       = 7;
int led5       = 8;
int fanPWM     = 9;
int fanSpeed   = 1;
bool dhtMode   = false; // set manual to true to add atomaticmode with DHT and AutoButton
bool automatic = false;
int dhtPin     = 10;
int autoButton = 11;
int temp       = 0;

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

  if (dhtMode) {
    pinMode(autoButton, INPUT_PULLUP);
    DHT dht(dhtPin, DHT11);
    dht.begin();
    pinMode(10, INPUT);
  }
}

void loop() {
  // Buttonwork
  if (!automatic) {
    if (!digitalRead(autoButton) && dhtMode) automatic = true; delay(300);
    if (!digitalRead(upButton))              fanSpeed++;       delay(300);
    if (!digitalRead(downButton))            fanSpeed--;       delay(300);
    if (fanSpeed>5)  fanSpeed = 5;
    if (fanSpeed<1)  fanSpeed = 1;
  } else {
    if (!digitalRead(autoButton)) automatic = false; delay(300);
    //temp = (int)dht.readTemperature();
    if      (temp <= 23) fanSpeed = 1;
    else if (temp <= 26) fanSpeed = 2;
    else if (temp <  29) fanSpeed = 3;
    else if (temp >  32) fanSpeed = 4;
    else if (temp >  35) fanSpeed = 5;
  }

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
