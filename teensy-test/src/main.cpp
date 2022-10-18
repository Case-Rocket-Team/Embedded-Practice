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

void get_registers(){
  select();
  SPI.transfer(0x05);
  byte reg1 = SPI.transfer(0);
  release();

  Serial.println("\nRegister-1:");
  Serial.println(reg1, BIN);

  select();
  SPI.transfer(0x35);
  byte reg2 = SPI.transfer(0);
  release();

  Serial.println("\nRegister-2:");
  Serial.println(reg2, BIN);
}

bool busy(){
  bool busy = true; 

  while(busy){
    Serial.println("Busy");
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

  SPI.transfer(0x52);
  SPI.transfer(one);
  SPI.transfer(two);
  SPI.transfer(three);

  release();

  Serial.println("Erase Beginning");
  unsigned long start, finished, elapsed;

  Serial.println("Start...");
  start=micros();
  while (busy()){
    Serial.println("Running Through Erase");

  }
  delay(500);
  finished=micros();
  Serial.println("Finished");
  elapsed=finished-start;
  Serial.print(elapsed);
  Serial.println(" microseconds elapsed");
  Serial.println();  
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

  get_registers();

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

void disable_write_protect(){
  write_enable();

  select();
  SPI.transfer(0x01);
  SPI.transfer(0b01111100);
  release();

}

void write_protect_fix(){
  get_registers();

  disable_write_protect();

  get_registers();
}

void reset(){
  select();
  SPI.transfer(0x66);
  release();

  select();
  SPI.transfer(0x99);
  release();
}

void disable_QPI(){
  select();
  SPI.transfer(0x38);
  release();
}




void setup() {
  initialize();

  manufacturer();

  get_registers();

  disable_QPI();

  get_registers();

  read_and_write_test();
}

void loop() {
  // put your main code here, to run repeatedly:
}

