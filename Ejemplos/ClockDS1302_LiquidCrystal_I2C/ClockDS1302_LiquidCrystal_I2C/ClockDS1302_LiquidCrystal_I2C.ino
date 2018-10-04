#include <DS1302.h>
#include <LiquidCrystal_I2C.h>

DS1302 rtc(4, 5, 6);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {

  Time t = rtc.time();
  char buff[20];
  
  sprintf(buff, "%02d/%02d/%4d", t.date, t.mon, t.yr);
  lcd.setCursor(3, 0);
  lcd.print(buff);
  sprintf(buff, "%02d:%02d:%02d", t.hr, t.min, t.sec);
  lcd.setCursor(4, 1);
  lcd.print(buff);
  delay(1000);
}
