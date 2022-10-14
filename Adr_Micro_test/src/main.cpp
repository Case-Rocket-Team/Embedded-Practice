#include <Arduino.h>
#include <SPI.h>

#define FLASH_CS_PIN A5


void setup() {
  pinMode(FLASH_CS_PIN, OUTPUT);

  digitalWrite(FLASH_CS_PIN, HIGH);

  SPI.begin();

  delay(2000);

  Serial.begin(9600); // bodrate

  Serial.println("Hello World");

  digitalWrite(FLASH_CS_PIN, LOW);

  SPI.beginTransaction(SPISettings(400000, MSBFIRST, SPI_MODE0));
  SPI.transfer(0x9F);

  delay(1);

  byte one = SPI.transfer(0);
  byte two = SPI.transfer(0);
  byte three = SPI.transfer(0);

  digitalWrite(FLASH_CS_PIN, HIGH);
  SPI.endTransaction();

  Serial.println(one, HEX);
  Serial.println(two, HEX);
  Serial.println(three, HEX);

}

void loop() {
  // put your main code here, to run repeatedly:

}

