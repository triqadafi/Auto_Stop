#include <Arduino.h>
#include <SoftwareSerial.h>
#include <PinChangeInterrupt.h>

#define PIN_RX 0
#define PIN_TX 1
#define PIN_PROXIMITY 2
#define PIN_INT_A 3
#define PIN_INT_B 4

SoftwareSerial blueToothSerial(0, 1); // RX, TX

volatile bool PIN_CHANGE = false;

void fi_pin_change(){
  PIN_CHANGE = true;
}

void setup() {
    // put your setup code here, to run once:

  //pinMode(PIN_PROXIMITY, INPUT_PULLUP);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(PIN_PROXIMITY), fi_pin_change, FALLING);
  pinMode(PIN_INT_A,OUTPUT); digitalWrite(PIN_INT_A, LOW);
  pinMode(PIN_INT_B,OUTPUT); digitalWrite(PIN_INT_A, LOW);

  blueToothSerial.begin(38400);
  digitalWrite(PIN_INT_A, HIGH);
  blueToothSerial.println("3913;39;1;");
  delay(1000);
  digitalWrite(PIN_INT_B, HIGH);
  blueToothSerial.println("3913;39;2;");
  digitalWrite(PIN_INT_A, LOW);
  digitalWrite(PIN_INT_B, LOW);
}

void loop() {
  if(PIN_CHANGE == true){
    blueToothSerial.println("3913;39;2;");
    delay(1000);
    PIN_CHANGE = false;
  }
}
