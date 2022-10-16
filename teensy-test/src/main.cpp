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
  select();

  SPI.transfer(0x9F);

  delay(1);

  byte one = SPI.transfer(0);
  byte two = SPI.transfer(0);
  byte three = SPI.transfer(0);

  release();

  Serial.println("Manufacturer:");
  Serial.println(one, HEX);
  Serial.println(two, HEX);
  Serial.println(three, HEX);


}


bool busy(){
  bool busy = true; 
  
  while(busy){
    select();
    SPI.transfer(0x05);
    byte resp = SPI.transfer(0);
    release();
    
    busy = resp & 0b00000001;
  }

  return false; 
}


void read(byte* read) {
  if(busy()){
    Serial.println("Busy.");
    return;
  }

  select();

  SPI.transfer(0x03);
  SPI.transfer(0);
  SPI.transfer(0);
  SPI.transfer(0);
  
  for (int i=0; i<4; i++){
    read[i] = SPI.transfer(0);
  }

  release();
}


void write_enable(){
  if (busy()) {
    Serial.println("Busy. Unable to enable write.");
    return;
  }
  
  select();

  SPI.transfer(0x06);

  release();

}

void erase(byte one, byte two, byte three){
  if (busy()) {
    Serial.println("Busy. Erase Failed.");
    return;
  }

  select();

  SPI.transfer(0x20);
  SPI.transfer(one);
  SPI.transfer(two);
  SPI.transfer(three);

  release();

  while (busy()){
    Serial.println("Running Through Erase");
    delay(500);
  }
}

void write(byte one, byte two, byte three){
  if (busy()) {
    Serial.println("Busy. Write Failed.");
    return;
  }

  select();

  SPI.transfer(0x02);

  SPI.transfer(one);
  SPI.transfer(two);
  SPI.transfer(three);

  SPI.transfer(0);
  SPI.transfer(0);
  SPI.transfer(0);
  SPI.transfer(0);
  
  release();

}


void write_zero(){
  if (busy()) {
    Serial.println("Busy. Write_Zero Failed.");
    return;
  }

  write_enable();

  erase(0, 0, 0);

  write(0, 0, 0);
}


void print_arr(byte A[]){
  // calculate size in bytes
  int arraySize = sizeof(A);
  int intSize = sizeof(A[0]);

  // length
  int length = arraySize / intSize;

  for (int i=0; i<length; i++){
    Serial.println(*(A+i), BIN);
  }
}


void read_test(){
  byte r[4];
  Serial.println("\nReading 0 0 0");
  read(r);
  
  print_arr(r);

}


void read_and_write_test(){
  byte r[4];
  Serial.println("\nReading 0 0 0");
  read(r);

  print_arr(r);

  Serial.println("\nWriting to 0 0 0");
  write_zero();

  Serial.println("\nReading 0 0 0");
  byte rf[4];
  read(rf);

  print_arr(rf);

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

  manufacturer();

  read_and_write_test();

}

void loop() {
  // put your main code here, to run repeatedly:
}

