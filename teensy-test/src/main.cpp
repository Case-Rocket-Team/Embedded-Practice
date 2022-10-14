#include <Arduino.h>
#include <SPI.h>

#define FLASH_CS_PIN 18


void select(){
  SPI.beginTransaction(SPISettings(400000, MSBFIRST, SPI_MODE0));

  digitalWrite(FLASH_CS_PIN, LOW);

}

void release(){
  SPI.endTransaction();
  digitalWrite(FLASH_CS_PIN, HIGH);
}

void manufacturer() {
  digitalWrite(FLASH_CS_PIN, LOW);

  SPI.transfer(0x9F);

  delay(1);

  byte one = SPI.transfer(0);
  byte two = SPI.transfer(0);
  byte three = SPI.transfer(0);

  digitalWrite(FLASH_CS_PIN, HIGH);

  Serial.println("Manufacturer:");
  Serial.println(one, HEX);
  Serial.println(two, HEX);
  Serial.println(three, HEX);


}

bool busy(){
  select();
  byte resp = SPI.transfer(0x05);
  release();
  
  return resp >> 0;
}

void read(byte* read) {
  if(busy()){
    Serial.println("Busy.");
    release();
    return;
  }
    
  SPI.transfer(0x03);
  SPI.transfer(0);
  SPI.transfer(0);
  SPI.transfer(0);
  
  for (int i=0; i<4; i++){
    read[i] = SPI.transfer(0);
  }

  release();
}

void write(){
  if (busy()) {
    Serial.println("Busy.");
    return;
  }

  select();

  SPI.transfer(0x06);

  SPI.transfer(0x02);

  SPI.transfer(0);
  SPI.transfer(0);
  SPI.transfer(0);

  SPI.transfer(0);
  SPI.transfer(0);
  SPI.transfer(0);
  SPI.transfer(0);
  
  SPI.transfer(0x04);

  release();
}



void read_test(){
  byte r[4];
  read(r);

  for (int i=0; i<4; i++){
    Serial.println(*(r+i));
  }

}


void read_and_write_test(){
  byte r[4];
  Serial.println("\nReading 0 0 0");
  read(r);

  for (int i=0; i<4; i++){
    Serial.println(*(r+i), BIN);
  }

  Serial.println("\nWriting to 0 0 0");
  write();

  Serial.println("\nReading 0 0 0");
  byte rf[4];
  read(rf);

  for (int i=0; i<4; i++){
    Serial.println(*(rf+i), BIN);
  }

}

void initialize(){
  pinMode(FLASH_CS_PIN, OUTPUT);
  digitalWrite(FLASH_CS_PIN, HIGH);

  SPI.begin();
  delay(500);
  Serial.begin(115200); // bodrate
  Serial.println("Initialized ");
}


void setup() {
  initialize();

  read_and_write_test();

}

void loop() {
  // put your main code here, to run repeatedly:
}
