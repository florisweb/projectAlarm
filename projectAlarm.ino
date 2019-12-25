#include <Display.h>

int powerPins[7] = {12, 10, 11, 9, 7, 8, 6};
int groundPins[4] = {2, 3, 4, 5};
Display display(powerPins, groundPins);

void setup() {
  Serial.begin(9600);
}



int runTimeIndex = 0;
String timeString = "";
void loop() {
  runTimeIndex++;
  if (runTimeIndex > 200)
  {
    runTimeIndex = 0;
    timeString = calcTimeString();
//    Serial.println(timeString);
  }
  
  display.writeString(timeString);
  delay(5);
}


String calcTimeString() {  
  unsigned long minutes = millis() / 1000 / 60 + (12 * 60 + 45);
  unsigned int hours = minutes / 60;
  minutes -= hours * 60;

  return timeToString(hours, minutes);
}

String timeToString(int hours, int minutes) {
  String hourString = String(hours);
  String minuteString = String(minutes);
  if (hours < 10) hourString = "0" + hourString;
  if (minutes < 10) minuteString = "0" + minuteString;

  return hourString + minuteString;
}
