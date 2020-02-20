
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
  blinkIndex = 0;
  blinkRate = 0;
}


void Display::writeString(String text) {
  digitIndex++;
  if (digitIndex > 3) digitIndex = 0;
  turnAllDigitsOff();

  blinkIndex++;
  if (blinkIndex > blinkRate) blinkIndex = 0;
  if (blinkIndex >= blinkRate * 0.3) digitalWrite(groundPins[digitIndex], LOW);

  updateDigitByString(text[digitIndex]);
}




void Display::updateDigitByString(char _string) {
  for (int i = 0; i < sizeof(powerPins) / sizeof(int); i++)
  {
    int curPin = powerPins[i];
    digitalWrite(curPin, LOW);
  }

  String pins = stringToPins(_string);

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



String Display::stringToPins(char _string) {
  if (_string == *"0") return "012456";
  if (_string == *"1") return "25";
  if (_string == *"2") return "02346";
  if (_string == *"3") return "02356";
  if (_string == *"4") return "1235";
  if (_string == *"5") return "01356";
  if (_string == *"6") return "013456";
  if (_string == *"7") return "025";
  if (_string == *"8") return "0123456";
  if (_string == *"9") return "012356";
  if (_string == *"_") return "6";
  return "";
}
