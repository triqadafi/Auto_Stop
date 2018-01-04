#include <Arduino.h>
#include <SoftwareSerial.h>
#include <PinChangeInterrupt.h>

#define PIN_RX 1
#define PIN_TX 0
#define PIN_PROXIMITY 2
#define PIN_INT_A 3
#define PIN_INT_B 4

SoftwareSerial blueToothSerial(PIN_RX, PIN_TX); // RX, TX

uint32_t FI_MS = 0;


void setup() {
  OSCCAL += -6;

  // Setup the IO
  pinMode(PIN_PROXIMITY, INPUT_PULLUP);
  pinMode(PIN_INT_A,OUTPUT); digitalWrite(PIN_INT_A, LOW);
  pinMode(PIN_INT_B,OUTPUT); digitalWrite(PIN_INT_B, LOW);

  // Start the Serial
  blueToothSerial.begin(9600);

  // INIT
  digitalWrite(PIN_INT_A, HIGH);
  digitalWrite(PIN_INT_B, HIGH);
  delay(1000);
  digitalWrite(PIN_INT_A, LOW);
  digitalWrite(PIN_INT_B, LOW);

  FI_MS = millis();
}


void loop() {
  if(millis() - FI_MS < 1000){
    digitalWrite(PIN_INT_A, HIGH);
  }else if(millis() - FI_MS < 2000){
    digitalWrite(PIN_INT_A, LOW);
  }else{
    FI_MS = millis();
  }
  if(digitalRead(PIN_PROXIMITY) == LOW){
    blueToothSerial.println("3913;FI+STOPWATCH=1;");
    digitalWrite(PIN_INT_A, LOW);
    digitalWrite(PIN_INT_B, HIGH);
    delay(5000);
    digitalWrite(PIN_INT_B, LOW);
    FI_MS = millis();
  }
}
