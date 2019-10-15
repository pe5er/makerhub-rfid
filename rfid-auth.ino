#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9         
#define SS_PIN 10

byte PeterBarnes[4]={16, 50, 76, 42};


MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Present RFID Tag to Reader"));
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  //Serial.print("UID=");
  //for(int i=0;i<4;i++){
  //Serial.print(mfrc522.uid.uidByte[i]);
  //Serial.print(" ");
  //}
  //Serial.println("");

  if(PeterBarnes[0] == mfrc522.uid.uidByte[0] && PeterBarnes[1] == mfrc522.uid.uidByte[1] && PeterBarnes[2] == mfrc522.uid.uidByte[2] && PeterBarnes[3] == mfrc522.uid.uidByte[3]){
    Serial.println("Welcome Peter Barnes");
  } else {
    Serial.println("Unknown User");
  }
}
