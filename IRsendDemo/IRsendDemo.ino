/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>

#include<LiquidCrystal.h>

LiquidCrystal lcd(0, 1, 8, 9, 10, 11);  // sets the interfacing pins

IRsend irsend;



int RECV_PIN = 12;

IRrecv irrecv(RECV_PIN);
int life = 20;
decode_results results;
int ammo = 90;


  // sets the interfacing pins


void setup()
{
  //Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  lcd.begin(16, 2);  // initializes the 16x2 LCD
  lcd.clear();
  irrecv.enableIRIn();
 
}

void loop() {
  int i;
  int sensorVal = digitalRead(2);
  Serial.println(sensorVal);
  if(sensorVal == 0 && ammo >= 1) {
	irsend.sendSony(0xa78, 12);
  delay(100);
  ammo--;
  }
  if(irrecv.decode(&results)){
        if(results.value == 0xa77)
    {
      Serial.println(results.value, HEX);
      if(life>0){
      life--;
      }
      irrecv.resume();
    }
    
  }
  lcd.setCursor(0,0);           //sets the cursor at row 0 column 0
  lcd.print("ammo");
  lcd.print(ammo);
  lcd.setCursor(2,1);           //sets the cursor at row 0 column 0
  lcd.print("life ");
  lcd.print(life);
  

}
