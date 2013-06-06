#include <DHT22.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include "editObject.h"

const int ConHeight = 2;
const int ConWidth = 16;

int milliseconds = 0;

LiquidCrystal_I2C lcd(0x20,ConWidth, ConHeight);
RTC_DS1307 rtc;
DHT22 myDHT22(9);

editObject godzina(3, 0, 0, 23, &lcd, NULL, NULL);
editObject minuta(6, 0, 0, 59, &lcd, NULL, &godzina);
editObject sekunda(9, 0, 0, 59, &lcd, &godzina, &minuta );
editObject temp(1, 1, 0, 100, &lcd, NULL, NULL);
editObject hum(12, 1, 0, 100, &lcd, NULL, NULL);

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

byte degree[8] = {
B01110,
B01010,
B01110,
B00000,
B00000,
B00000,
B00000
};


void setup()
{
  lcd.init();
  lcd.backlight();
  Wire.begin();
  rtc.begin();
  godzina.setLeadingChar(' ');
  minuta.setLeadingChar(':');
  sekunda.setLeadingChar(':');
  temp.setLeadingChar('=');  
  hum.setLeadingChar('=');
  lcd.createChar(0, updown);
  lcd.createChar(1, left);
  lcd.createChar(2, right);
  lcd.createChar(3, degree);
  lcd.setCursor(0,0);
  sekunda.setReadOnly(false);
  sekunda.setActive(false);
}

void loop() 
{
  delay(100);
  DHT22_ERROR_t errorCode;
  if (millis()-milliseconds >=2000)
  {
    if (myDHT22.readData() == DHT_ERROR_NONE)
    {
      temp.setValue(myDHT22.getTemperatureC());
      hum.setValue(myDHT22.getHumidity());
      lcd.setCursor(0,1);
      lcd.print('T');
      temp.print();
      lcd.write(byte(3));
      lcd.print('C');
      lcd.setCursor(11,1);
      lcd.print('H');
      hum.print();
      lcd.print('%');
      milliseconds=millis();
    }
  }
  
  
  if (rtc.isrunning())
  {
    DateTime now = rtc.now();
    godzina.setValue(now.hour());
    minuta.setValue(now.minute());
    sekunda.setValue(now.second());
    displayTime(&godzina, &minuta, &sekunda);
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("Nie dziala RTC");
  }
}
