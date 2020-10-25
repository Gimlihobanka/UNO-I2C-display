/*
RTC PCF8563 + IIC LCD Prevodnik. Adresa LCD PCF8574_ADDR_A21_A11_A01

*/


#include <Arduino.h>
#include <Wire.h>              //for ESP8266 use bug free i2c driver https://github.com/enjoyneering/ESP8266-I2C-Driver
#include <LiquidCrystal_I2C.h>
#include <Rtc_Pcf8563.h>


#define COLUMS           20
#define ROWS             4

#define LCD_SPACE_SYMBOL 0x20  //space symbol from the LCD ROM, see p.9 of GDM2004D datasheet

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);
Rtc_Pcf8563 rtc;

void setup()
{
  Serial.begin(9600);

  while (lcd.begin(COLUMS, ROWS) != 1) //colums - 20, rows - 4
  {
    Serial.println(F("PCF8574 is not connected or lcd pins declaration is wrong. Only pins numbers: 4,5,6,16,11,12,13,14 are legal."));
    delay(5000);   
  }

  Serial.println(F("PCF8574 OK"));
  lcd.noBacklight();
  lcd.print(F("PCF8574 is OK..."));    //(F()) saves string to flash & keeps dynamic memory free
  delay(2000);
  lcd.backlight();
  lcd.clear();

  //lcd.setCursor(0, 1);
  lcd.blink();

  /* prints static text */
  lcd.setCursor(0, 0);                 //set 1-st colum & 2-nd row, 1-st colum & row started at zero
  lcd.print(F("Hello world!"));

  lcd.setCursor(0, 1);
  lcd.print(F("Random number:"));


  rtc.initClock();
  //set a time to start with.
  //day, weekday, month, century, year
  rtc.setDate(14, 6, 3, 0, 10);
  //hr, min, sec
  rtc.setTime(1, 15, 40);
}
//test git

//Obnova testovani GIT

void loop()
{
  lcd.setCursor(0, 2);
  //lcd.print(rtc.formatTime(RTCC_TIME_HM));
  lcd.print(rtc.formatTime());
  lcd.setCursor(0, 3);
  //lcd.print(rtc.formatDate(RTCC_DATE_ASIA));
  lcd.print(rtc.formatDate());
  delay(100);

  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.setCursor(15, 0);
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
     }
    }
}