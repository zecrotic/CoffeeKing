void SingleClickForProfileOne()
{
  buttonPushCounter = EEPROM.read(0);
  sugarButtonPushCounter = EEPROM.read(1);
  turnOnLeds();
  delay(10);
}

void LongClickForProfileOne()
{
  userSettingOneForCream = buttonPushCounter;
  userSettingOneForSugar = sugarButtonPushCounter;
  EEPROM.write(0, userSettingOneForCream);
  EEPROM.write(1, userSettingOneForSugar);
}

void SingleClickForProfileTwo()
{
  buttonPushCounter = EEPROM.read(2);
  sugarButtonPushCounter = EEPROM.read(3);
  turnOnLeds();
  delay(10);
}

void LongClickForProfileTwo()
{
  userSettingTwoForCream = buttonPushCounter;
  userSettingTwoForSugar = sugarButtonPushCounter;
  EEPROM.write(2, userSettingTwoForCream);
  EEPROM.write(3, userSettingTwoForSugar);
}
