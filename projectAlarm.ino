#include <Display.h>

int powerPins[7] = {12, 10, 11, 9, 7, 8, 6};
int groundPins[4] = {2, 3, 4, 5};
Display display(powerPins, groundPins);

const int potentialMinutePin = A1;
const int potentialHourPin = A0;
const int stateButtonPin = A2;

const int stateLEDRedPin = A3;
const int stateLEDGreenPin = A5;
const int stateLEDBluePin = A4;



int runTimeIndex = 0;
boolean prevStateButtonStatus = false;

unsigned long previousMillis = 0;
unsigned long minutes = 21 * 60 + 13;
unsigned long alarmMinutes = 0;

int prevMinuteVal = 0;
int prevHourVal = 0;

int timeEditing_deltaTime = 0;
int systemState = 0;
// 0: time
// 1: alarm
// 2: set time
// 3: set alarm





void setup() {
  Serial.begin(9600);
  display.blinkRate = 0;

  pinMode(stateLEDRedPin, OUTPUT);
  pinMode(stateLEDGreenPin, OUTPUT);
  pinMode(stateLEDBluePin, OUTPUT);
}






String timeString = "";
void loop() {
  handleInputs();

  if (minutes >= alarmMinutes && systemState == 1)
  {
    display.blinkRate = 100;
  } else {
    display.blinkRate = 0;
  }
  //
  //  Serial.print("Alarm: ");
  //  Serial.print(alarmMinutes);
  //  Serial.print(" Time: ");
  //  Serial.println(minutes);

  switch (systemState)
  {
    case 3: timeString = calcTimeString(alarmMinutes); break;
    default: timeString = calcTimeString(minutes); break;
  }


  runTimeIndex++;
  if (runTimeIndex > 100) runTimeIndex = 0;
  if (runTimeIndex % 10 == 0) updateTime();



  display.writeString(timeString);
  delay(5);
}

void handleInputs() {
  handlePotentialMeterInputs();

  boolean stateButtonPressed = digitalRead(stateButtonPin);
  if (stateButtonPressed != prevStateButtonStatus && stateButtonPressed == true) updateSystemState();
  prevStateButtonStatus = stateButtonPressed;
}

void handlePotentialMeterInputs() {
  if (systemState < 2) return;
  int addedMinutes = getPotentialMeterInputInMinutes();

  switch (systemState)
  {
    case 2:
      if (-addedMinutes > minutes) minutes += 24 * 60;
      minutes += addedMinutes;
      if (minutes > 24 * 60) minutes -= 24 * 60;

      break;
    case 3:
      if (-addedMinutes > alarmMinutes) alarmMinutes += 24 * 60;
      alarmMinutes += addedMinutes;
      if (alarmMinutes > 24 * 60) alarmMinutes -= 24 * 60;

      break;
  }

}


long getPotentialMeterInputInMinutes() {
  int addMinutes = 60 - analogRead(potentialMinutePin) / 17;
  int _minutes = addMinutes - prevMinuteVal;
  prevMinuteVal = addMinutes;

  int addHours = 24 - analogRead(potentialHourPin) / 42;
  int _hours = addHours - prevHourVal;
  prevHourVal = addHours;

  return _minutes + _hours * 60;
}








String calcTimeString(int _minutes) {
  unsigned int hours = _minutes / 60;
  int displayMinutes = _minutes - hours * 60;

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



void updateSystemState() {
  systemState++;
  if (systemState > 3) systemState = 0;
  Serial.print("Systemstate: ");
  Serial.println(systemState);

  timeEditing_deltaTime = 0;
  setSystemStateConfig();
}

void setSystemStateConfig() {
  switch (systemState)
  {
    case 0:
      setSystemStateLED(0, 0, 0);
      display.blinkRate = 0;
      break;
    case 1:
      setSystemStateLED(255, 0, 0);
      display.blinkRate = 0;
      break;
    case 2:
      setSystemStateLED(0, 255, 0);
      //      display.blinkRate = 100;
      break;
    case 3:
      setSystemStateLED(0, 0, 255);
      //      display.blinkRate = 100;
      break;
  }
}

void setSystemStateLED(int r, int g, int b) {
  analogWrite(stateLEDRedPin, r);
  analogWrite(stateLEDGreenPin, g);
  analogWrite(stateLEDBluePin, b);
}
