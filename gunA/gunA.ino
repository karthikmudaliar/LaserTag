/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>
#include <EEPROM.h>

#include<LiquidCrystal.h>
#define rumble 13
#define buzz 7

LiquidCrystal lcd(0, 1, 8, 9, 10, 11);  // sets the interfacing pins

IRsend irsend;



int RECV_PIN = 12;

IRrecv irrecv(RECV_PIN);
int life = 20;
decode_results results;
int ammo = 90;
int lifeaddr = 0;
int ammoaddr = 1;
#define rumble 13

  // sets the interfacing pins


void setup()
{
//  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  lcd.begin(16, 2);  // initializes the 16x2 LCD
  lcd.clear();
  irrecv.enableIRIn();
  EEPROM.write(lifeaddr, life);
  EEPROM.write(ammoaddr, ammo);
  pinMode(rumble, OUTPUT);
  digitalWrite(rumble, LOW);
  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, LOW);
}

void loop() {
  int i;
  int sensorVal = digitalRead(2);
  life = EEPROM.read(lifeaddr);
  ammo = EEPROM.read(ammoaddr); 
//  Serial.println(sensorVal);
  if(sensorVal == 0 && ammo >= 1 && life >= 1) {
	irsend.sendSony(0xa78, 12);
  digitalWrite(rumble, HIGH);
  delay(100);
  ammo--;
  EEPROM.write(ammoaddr, ammo);
  irrecv.enableIRIn();
  }
  digitalWrite(rumble, LOW);
  if(irrecv.decode(&results)){
        if(results.value == 0xa77)
 {
      Serial.println(results.value, HEX);
      if(life>0){
      life--;
      EEPROM.write(lifeaddr, life);
      Serial.print("life");
      Serial.println(life);
      if(life == 0){
        digitalWrite(buzz,HIGH);
      }
      }
    }      
    irrecv.resume();
//    irrecv.enableIRIn();
    
  }
    
  lcd.setCursor(0,0);           //sets the cursor at row 0 column 0
  lcd.print("ammo");
  lcd.print(ammo);
  lcd.setCursor(2,1);           //sets the cursor at row 0 column 0
  lcd.print("life ");
  lcd.print(life);
  
  

}
