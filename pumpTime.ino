
void pumpTime(int cream, int sugar) {
  if (startState == LOW) {
    int time = cream * 100;
    digitalWrite(pump, HIGH);
    delay(time);
    digitalWrite(pump, LOW);
    for (int numOfSugar = 0; numOfSugar < sugar; numOfSugar++)
    {
      servo1.write(180);
      delay(1250); // The delays have to be fairly long here
      servo1.write(-180);
      delay(1250); // The delays have to be fairly long here
    }
    digitalWrite(stirMotor, HIGH);
    delay(500);
    digitalWrite(stirMotor, LOW);
  }
}
