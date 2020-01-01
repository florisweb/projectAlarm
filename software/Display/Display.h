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
    void updateDigitByNumber(int number);
    void turnAllDigitsOff();
    String numberToPins(int number);
    int powerPins[7];
    int groundPins[4];
    int digitIndex;
    int blinkIndex;
};




#endif