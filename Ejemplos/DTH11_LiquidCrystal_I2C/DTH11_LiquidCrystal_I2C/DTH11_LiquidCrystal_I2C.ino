#include <DHT11.h>
#include <LiquidCrystal_I2C.h>

DHT11 dht11(A1);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  
  int err;
  float temp, hum;
  char buff[20];
  
  if((err = dht11.read(hum, temp)) == 0) {
  
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura: " + String((int)temp));
    
    lcd.setCursor(0, 1);
    lcd.print("Humedad: " + String((int)hum));
    
  } else {

    lcd.clear();
    sprintf(buff, "Error num: %d", err);
    lcd.setCursor(0, 0);
    lcd.print(buff);
  }
  delay(1000);
}
