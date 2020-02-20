#ifndef Display_h
#define Display_h



#include "Arduino.h"

class Display
{
  public:
    Display(int _powerPins[7], int _groundPins[4]);
    void writeString(String text);
    int blinkRate; // / 100: percent of the time off
  private:
    void updateDigitByString(char _string);
    void turnAllDigitsOff();
    String stringToPins(char _string);
    int powerPins[7];
    int groundPins[4];
    int digitIndex;
    int blinkIndex;
};




#endif