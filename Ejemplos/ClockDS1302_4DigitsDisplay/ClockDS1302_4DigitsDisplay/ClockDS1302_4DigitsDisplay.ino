#include "DS1302.h"
#include "Disp7S4D.h"
#include <stdio.h>

//DS1302 rtc(Chip Enable, Input/Output, Serial Clock);
DS1302 rtc(9, 10, 11);

//Segmentos del display de 7 segmentos abcdefg:
const int segs[] = {2, 3, 4, 5, 6, 7, 8, 13};

//Dígitos del display de 7 segmentos d1, d2, d3, d4
int digits[] = {A0, A1, A2, A3}; 

Disp7S4D disp(segs, digits);

void setup() {
  
  // Initialize a new chip by turning off write protection and clearing the
  // clock halt flag. These methods needn't always be called. See the DS1302
  // datasheet for details.
  rtc.writeProtect(true);
  rtc.halt(false);

  // Set the time and date on the chip.
  //rtc.time(Time(__DATE__, __TIME__));
}

void loop() {

  Time t = rtc.time();
  disp.printTime(t.hr, t.min);
}
