//sending pot
//recieving led
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define led 13
RF24 radio(9, 10); // CE, CSN
const byte addresses[][6] = {"00103",};
boolean buttonState = 0;
void setup() {
pinMode(13, OUTPUT);
radio.begin();
radio.openWritingPipe(addresses[1]); // 00002
radio.openReadingPipe(1, addresses[0]); // 00001
radio.setPALevel(RF24_PA_MIN);
}
void loop() {
delay(5);
radio.stopListening();
int potValue = analogRead(A0);
int angleValue = map(potValue, 0, 658, 0, 255);
radio.write(&angleValue, sizeof(angleValue));
delay(5);
radio.startListening();
while (!radio.available());
radio.read(&buttonState, sizeof(buttonState));
if (buttonState == LOW) {
digitalWrite(led, HIGH);
}
else {
digitalWrite(led, LOW);
}
}
