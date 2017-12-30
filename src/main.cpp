#include <Arduino.h>
#include <SoftwareSerial.h>
#include <PinChangeInterrupt.h>

#define PIN_RX 1
#define PIN_TX 0
#define PIN_PROXIMITY 2
#define PIN_INT_A 3
#define PIN_INT_B 4

SoftwareSerial blueToothSerial(PIN_RX, PIN_TX); // RX, TX

void setup() {
  // Setup the IO
  pinMode(PIN_PROXIMITY, INPUT_PULLUP);
  pinMode(PIN_INT_A,OUTPUT); digitalWrite(PIN_INT_A, LOW);
  pinMode(PIN_INT_B,OUTPUT); digitalWrite(PIN_INT_A, LOW);

  // Start the Serial
  blueToothSerial.begin(38400);

  // INIT
  blueToothSerial.println("3913;39;1;");
  delay(1000);
  blueToothSerial.println("3913;39;2;");

  digitalWrite(PIN_INT_A, HIGH);
  digitalWrite(PIN_INT_B, HIGH);
  delay(1000);
  digitalWrite(PIN_INT_A, LOW);
  digitalWrite(PIN_INT_B, LOW);
}

void loop() {
  if(digitalRead(PIN_PROXIMITY) == LOW){
    blueToothSerial.println("3913;39;2;");
    delay(3000);
  }
}
