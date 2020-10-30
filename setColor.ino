void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redLedPinForSugarSensor, redValue);
  analogWrite(greenLedPinForSugarSensor, greenValue);
  analogWrite(blueLedPinForSugarSensor, blueValue);
}
