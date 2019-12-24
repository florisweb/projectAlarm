const int digitPowerPorts[7] = {12, 10, 11, 9, 7, 8, 6};
const int digitGroundPorts[4] = {2, 3, 4, 5};

void setup() {
  Serial.begin(9600);
  Serial.println("Start");

  for (int i = 0; i < sizeof(digitPowerPorts) / sizeof(int); i++)
  {
    pinMode(digitPowerPorts[i], OUTPUT);
    digitalWrite(digitPowerPorts[i], LOW);
  }

  for (int i = 0; i < sizeof(digitGroundPorts) / sizeof(int); i++)
  {
    pinMode(digitGroundPorts[i], OUTPUT);
    digitalWrite(digitGroundPorts[i], HIGH);
  }
}



int iterator[4] = {0, 0, 0, 0};
int runTimeIndex = 0;
int digitIndex = 0;

void loop() {
  runTimeIndex++;
  if (runTimeIndex > 10)
  {
    runTimeIndex = 0;
    iterator[0]++;
    if (iterator[0] > 9) {iterator[0] = 0; iterator[1]++;}
    if (iterator[1] > 9) {iterator[1] = 0; iterator[2]++;}
    if (iterator[2] > 9) {iterator[2] = 0; iterator[3]++;}
    if (iterator[3] > 9) {iterator[3] = 0;}
  }
  
  digitIndex++;
  if (digitIndex > 3) digitIndex = 0;
  turnAllDigitsOff();
  digitalWrite(digitGroundPorts[digitIndex], LOW);
  updateDigitByNumber(iterator[3 - digitIndex]);
  
  delay(5);
}





int curPinIndex = 0;
void updateDigitByNumber(int number) {
  turnAllLEDsOff();
  String pins = numberToPins(number);
//  curPinIndex++;
//  if (curPinIndex >= pins.length())
//  {
//    curPinIndex = 0; 
//  }
  
//  Serial.print(pins.length());
//  Serial.print(" digit: ");
//  Serial.println(pins);

  for (int i = 0; i < pins.length(); i++)
  {
     int curPin = pins[i] - 48;
    digitalWrite(digitPowerPorts[curPin], HIGH);
  }

 
}

void turnAllLEDsOff() {
  for (int i = 0; i < sizeof(digitPowerPorts) / sizeof(int); i++)
  {
    int curPin = digitPowerPorts[i];
    digitalWrite(curPin, LOW);
  }
}


void turnAllDigitsOff() {
  for (int i = 0; i < sizeof(digitGroundPorts) / sizeof(int); i++)
  {
    int curPin = digitGroundPorts[i];
    digitalWrite(curPin, HIGH);
  }
}






String numberToPins(int number) {
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
    default: return "012356"; break;
  }
}
