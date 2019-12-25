#include <Display.h>

int a[7] = {12, 10, 11, 9, 7, 8, 6};
int b[4] = {2, 3, 4, 5};
Display display(a, b);

void setup() {
  Serial.begin(9600);
}



int iterator[4] = {0, 0, 0, 0};
int runTimeIndex = 0;

void loop() {
  //  runTimeIndex++;
  //  if (runTimeIndex > 10)
  //  {
  //    runTimeIndex = 0;
  //    iterator[0]++;
  //    if (iterator[0] > 9) {iterator[0] = 0; iterator[1]++;}
  //    if (iterator[1] > 9) {iterator[1] = 0; iterator[2]++;}
  //    if (iterator[2] > 9) {iterator[2] = 0; iterator[3]++;}
  //    if (iterator[3] > 9) {iterator[3] = 0;}
  //  }

  display.writeString("232");

  delay(5);
}
