#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Disp7S4D.h"

static const String Disp7S4D::numbers[] = {
  "11111100", //0
  "01100000", //1
  "11011010", //2
  "11110010", //3
  "01100110", //4
  "10110110", //5
  "10111110", //6
  "11100000", //7
  "11111110", //8
  "11110110"  //9
};

Disp7S4D::Disp7S4D(const int PIN_SEGS[8], const int PIN_DIGITS[4]) {

  segs = PIN_SEGS;
  digits = PIN_DIGITS;

  for (int i = 0; i < 8; i++) {
    pinMode(segs[i], OUTPUT);
  }
  
  for (int i = 0; i < 4; i++) {
    pinMode(digits[i], OUTPUT);
  }
}

void Disp7S4D::printNum(const int& number) {
  //digitalWrite(digits[3], HIGH);
  
  for (int i = 0; i < 7; i++) {
    
    if (numbers[number].charAt(i) == '1') {
      
      digitalWrite(segs[i], LOW);
      
    } else {
      
      digitalWrite(segs[i], HIGH);
    }
  }

  digitalWrite(segs[7], HIGH);
}

void Disp7S4D::printTime(const int& hour, const int& min) {

  int d[] = {floor(hour / 10), hour - 10 * floor(hour / 10), floor(min / 10), min - 10 * floor(min / 10)};

  for (int i = 0; i < 4; i++) {
    
    if (i != 0) {

      digitalWrite(digits[i - 1], LOW);
    }
    
    if (i == 0) {
      
      digitalWrite(digits[3], LOW);
    }
    
    digitalWrite(digits[i], HIGH);
    printNum(d[i]);
    delay(5);
  }
}
