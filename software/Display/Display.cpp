
#include "Arduino.h"
#include "display.h"

Display::Display(int _powerPins[7], int _groundPins[4])
{
  for (int p = 0; p < 7; p++) 
  {
    powerPins[p] = _powerPins[p];
    pinMode(powerPins[p], OUTPUT);
    digitalWrite(powerPins[p], LOW);
  }
   
  for (int g = 0; g < 4; g++) 
  {
    groundPins[g] = _groundPins[g];
    pinMode(groundPins[g], OUTPUT);
    digitalWrite(groundPins[g], HIGH);
  }

  digitIndex = 0;
}


void Display::writeString(String text) {
  
  digitIndex++;
  if (digitIndex > 3) digitIndex = 0;
  turnAllDigitsOff();
  digitalWrite(groundPins[digitIndex], LOW);

  updateDigitByNumber(text[digitIndex] - 48);
}




void Display::updateDigitByNumber(int number) {
  for (int i = 0; i < sizeof(powerPins) / sizeof(int); i++)
  {
    int curPin = powerPins[i];
    digitalWrite(curPin, LOW);
  }

  String pins = numberToPins(number);

  for (int i = 0; i < pins.length(); i++)
  {
    int curPin = pins[i] - 48;
    digitalWrite(powerPins[curPin], HIGH);
  }
}


void Display::turnAllDigitsOff() {
  for (int i = 0; i < sizeof(groundPins) / sizeof(int); i++)
  {
    int curPin = groundPins[i];
    digitalWrite(curPin, HIGH);
  }
}



String Display::numberToPins(int number) {
  switch (number) {
    case 0: return "012456"; break;
    case 1: return "25"; break;
    case 2: return "02346"; break;
    case 3: return "02356"; break;
    case 4: return "1235"; break;
    case 5: return "01356"; break;
    case 6: return "013456"; break;
    case 7: return "025"; break;
    case 8: return "0123456"; break;
    case 9: return "012356"; break;
    default: return ""; break;
  }
}
