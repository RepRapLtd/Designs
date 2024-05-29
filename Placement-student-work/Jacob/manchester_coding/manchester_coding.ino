

#include "Manchester.h"


#define TX_PIN  18  //pin where your transmitter is connected
#define RX_PIN 19
#define LED_PIN 13

uint8_t moo = 1;
#define BUFFER_SIZE 22
uint8_t buffer[BUFFER_SIZE];



void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);  
  digitalWrite(LED_PIN, moo);
  pinMode(TX_PIN, OUTPUT);
  digitalWrite(TX_PIN, 0);
  Serial.begin(19200);
  man.setupReceive(RX_PIN, MAN_19200);
  man.beginReceiveArray(BUFFER_SIZE, buffer);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (man.receiveComplete()) 
  {
    uint8_t receivedSize = 0;

    //do something with the data in 'buffer' here before you start receiving to the same buffer again
    receivedSize = buffer[0];
    for(uint8_t i=1; i<receivedSize; i++)
      Serial.write(buffer[i]);
    
    Serial.println();

    man.beginReceiveArray(BUFFER_SIZE, buffer);
    moo = ++moo % 2;
    digitalWrite(LED_PIN, moo);

} }
