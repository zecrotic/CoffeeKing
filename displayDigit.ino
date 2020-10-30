void displayDigit(int digit, int pins[])
{
  switch (digit) //Case number will be the displayed digit
  {
    case 0:
      digitalWrite(pins[0], HIGH);
      digitalWrite(pins[1], HIGH);
      digitalWrite(pins[2], HIGH);
      digitalWrite(pins[3], HIGH);
      digitalWrite(pins[4], HIGH);
      digitalWrite(pins[5], HIGH);
      digitalWrite(pins[6], LOW);
      break;
    case 1:
      digitalWrite(pins[0], LOW);
      digitalWrite(pins[1], HIGH);
      digitalWrite(pins[2], HIGH);
      digitalWrite(pins[3], LOW);
      digitalWrite(pins[4], LOW);
      digitalWrite(pins[5], LOW);
      digitalWrite(pins[6], LOW);
      break;
    case 2:
      digitalWrite(pins[0], HIGH);
      digitalWrite(pins[1], HIGH);
      digitalWrite(pins[2], LOW);
      digitalWrite(pins[3], HIGH);
      digitalWrite(pins[4], HIGH);
      digitalWrite(pins[5], LOW);
      digitalWrite(pins[6], HIGH);
      break;
    case 3:
      digitalWrite(pins[0], HIGH);
      digitalWrite(pins[1], HIGH);
      digitalWrite(pins[2], HIGH);
      digitalWrite(pins[3], HIGH);
      digitalWrite(pins[4], LOW);
      digitalWrite(pins[5], LOW);
      digitalWrite(pins[6], HIGH);
      break;
    case 4:
      digitalWrite(pins[0], LOW);
      digitalWrite(pins[1], HIGH);
      digitalWrite(pins[2], HIGH);
      digitalWrite(pins[3], LOW);
      digitalWrite(pins[4], LOW);
      digitalWrite(pins[5], HIGH);
      digitalWrite(pins[6], HIGH);
      break;
    case 5:
      digitalWrite(pins[0], HIGH);
      digitalWrite(pins[1], LOW);
      digitalWrite(pins[2], HIGH);
      digitalWrite(pins[3], HIGH);
      digitalWrite(pins[4], LOW);
      digitalWrite(pins[5], HIGH);
      digitalWrite(pins[6], HIGH);
      break;
    case 6:
      digitalWrite(pins[0], HIGH);
      digitalWrite(pins[1], LOW);
      digitalWrite(pins[2], HIGH);
      digitalWrite(pins[3], HIGH);
      digitalWrite(pins[4], HIGH);
      digitalWrite(pins[5], HIGH);
      digitalWrite(pins[6], HIGH);
      break;
    case 7:
      digitalWrite(pins[0], HIGH);
      digitalWrite(pins[1], HIGH);
      digitalWrite(pins[2], HIGH);
      digitalWrite(pins[3], LOW);
      digitalWrite(pins[4], LOW);
      digitalWrite(pins[5], LOW);
      digitalWrite(pins[6], LOW);
      break;
    case 8:
      digitalWrite(pins[0], HIGH);
      digitalWrite(pins[1], HIGH);
      digitalWrite(pins[2], HIGH);
      digitalWrite(pins[3], HIGH);
      digitalWrite(pins[4], HIGH);
      digitalWrite(pins[5], HIGH);
      digitalWrite(pins[6], HIGH);
      break;
    case 9:
      digitalWrite(pins[0], HIGH);
      digitalWrite(pins[1], HIGH);
      digitalWrite(pins[2], HIGH);
      digitalWrite(pins[3], HIGH);
      digitalWrite(pins[4], LOW);
      digitalWrite(pins[5], HIGH);
      digitalWrite(pins[6], HIGH);
      break;
    case 10:
      digitalWrite(pins[0], LOW);
      digitalWrite(pins[1], LOW);
      digitalWrite(pins[2], LOW);
      digitalWrite(pins[3], LOW);
      digitalWrite(pins[4], LOW);
      digitalWrite(pins[5], LOW);
      digitalWrite(pins[6], LOW);
      break;


  }
}
