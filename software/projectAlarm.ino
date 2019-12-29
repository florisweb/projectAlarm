#include <Display.h>

int powerPins[7] = {12, 10, 11, 9, 7, 8, 6};
int groundPins[4] = {2, 3, 4, 5};
Display display(powerPins, groundPins);

void setup() {
  Serial.begin(9600);
}



int runTimeIndex = 0;

unsigned long previousMillis = 0;
unsigned long minutes = 15 * 60 + 19;

String timeString = "";
void loop() {
  

  runTimeIndex++;
  if (runTimeIndex > 200)
  {
    runTimeIndex = 0;
    timeString = calcTimeString();
  }
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
