#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>
#include "editObject.h"
#include "relayChannel.h"

LiquidCrystal lcd(8,9,4,5,6,7);
RTC_DS1307 rtc;
editObject godzina(3, 0, 0, 23, &lcd, NULL, NULL);
editObject minuta(6, 0, 0, 59, &lcd, NULL, &godzina);
editObject sekunda(9, 0, 0, 59, &lcd, &godzina, &minuta );
relayChannel channel1(13, false, false, event, 1, 3);

byte updown[8] = {
  B00100,
  B01110,
  B11111,
  B00000,
  B00000,
  B11111,
  B01110,
  B00100
};

byte left[8] = {
  B00001,
  B00011,
  B00111,
  B01111,
  B00111,
  B00011,
  B00001
};

byte right[8] = {
B10000,
B11000,
B11100,
B11110,
B11100,
B11000,
B10000
};

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  Wire.begin();
  rtc.begin();
  godzina.setLeadingChar(' ');
  minuta.setLeadingChar(':');
  sekunda.setLeadingChar(':');  
  lcd.createChar(0, updown);
  lcd.createChar(1, left);
  lcd.createChar(2, right);
  lcd.setCursor(0,0);
//  lcd.write(byte(0));
  godzina.setReadOnly(true);
  godzina.setEditMode(true);
  //godzina.setActive(true);
}

void loop() 
{
  
  if (rtc.isrunning())
  {
    DateTime now = rtc.now();
    //lcd.setCursor(0,0);
    //lcd.print(now.hour());
    godzina.setValue(now.hour());
    godzina.print();
    minuta.setValue(now.minute());
    minuta.print();
    sekunda.setValue(now.second());
    sekunda.print();
   
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("Nie dziala RTC");
  }
  
  
}
