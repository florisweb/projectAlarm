#include <Display.h>

int powerPins[7] = {12, 10, 11, 9, 7, 8, 6};
int groundPins[4] = {2, 3, 4, 5};
Display display(powerPins, groundPins);

const int potentialMinutePin = A1;
const int potentialHourPin = A0;
const int stateButtonPin = A2;



int runTimeIndex = 0;

unsigned long previousMillis = 0;
unsigned long minutes = 0;//15 * 60 + 19;

int previousAddedMinutes = 0;
int previousAddedHours = 0;

int systemState = 0;
// 0: time
// 1: alarm
// 2: set time
// 3: set alarm





void setup() {
  Serial.begin(9600);
  display.blinkRate = 150;
}






String timeString = "";
void loop() {

  int addMinutes = 60 - analogRead(potentialMinutePin) / 17;
  minutes += addMinutes - previousAddedMinutes;
  previousAddedMinutes = addMinutes;

  int addHours = 24 - analogRead(potentialHourPin) / 42;
  minutes += (addHours - previousAddedHours) * 60;
  previousAddedHours = addHours;

  //  boolean blinking = digitalRead(stateButtonPin);
  //  Serial.println(blinking);

  timeString = calcTimeString();
  runTimeIndex++;
  if (runTimeIndex > 100) runTimeIndex = 0;
  if (runTimeIndex % 10 == 0) updateTime();



  display.writeString(timeString);
  delay(5);
}



String calcTimeString() {
  unsigned int hours = minutes / 60;
  int displayMinutes = minutes - hours * 60;

  return timeToString(hours, displayMinutes);
}

String timeToString(int hours, int minutes) {
  String hourString = String(hours);
  String minuteString = String(minutes);
  if (hours < 10) hourString = "0" + hourString;
  if (minutes < 10) minuteString = "0" + minuteString;

  return hourString + minuteString;
}

void updateTime() {
  if ((millis() - previousMillis) / 1000 >= 60)
  {
    minutes++;
    if (minutes >= 60 * 24) minutes = 0;
    previousMillis = millis();
  }
}
