//Video https://www.youtube.com/watch?v=jtmUxgDf6uI&t=4s
//Website with schematic https://www.viralsciencecreativity.com/post/arduino-seven-segment-display-counter-push-button-code-explanation
/*
   I currently only have one seven segment display so
   I'm treating it as the user gets equal part sugar and cream.
   This will be easy to fix later.
   You can use the links above to set up most of this yourself.
   The code has been modified so that the counter cannot go above 9 or below 0
   and the the count can be decremented.
   I'm also using a switch statement to display the numbers
   instead of a bunch of if statements for legability and efficiency.
*/
#include <Servo.h> //Adds the libraries for the servo
#include "OneButton.h" //Add OneButton library
#include<EEPROM.h> //Allows the user to save their profile in the event of a reset

Servo servo1; //Servo for sugar dispenser
OneButton userProfile1(A6, true); //Attches the user profile 1 button to pin A6
OneButton userProfile2(A7, true); //Attches the user profile 2 button to pin A7

const int a = 29;  //For displaying segment "a"
const int b = 31;  //For displaying segment "b" // This one is bad
const int c = 42;  //For displaying segment "c"
const int d = 41;  //For displaying segment "d"
const int e = 44;  //For displaying segment "e"
const int f = 24;  //For displaying segment "f"
const int g = 22;  //For displaying segment "g"

const int a_sugar = 30;  //For displaying segment "a"//this one is bad
const int b_sugar = 32;  //For displaying segment "b"
const int c_sugar = 39;  //For displaying segment "c"
const int d_sugar = 38;  //For displaying segment "d"
const int e_sugar = 40;  //For displaying segment "e"
const int f_sugar = 28;  //For displaying segment "f"
const int g_sugar = 26;  //For displaying segment "g"

const int pump = 7;  //Pump for cream
const int stirMotor = 2;

const int buttonPin = 25; //Attached to the button that increments the count // Tis connection is bad
const int decrementButtonPin = 36; //Attached to the button to decrement the count
const int sugarButtonPin = 27;
const int sugarDecrementButtonPin = 49;
const int start = 34; //Button to start the process of adding cream and sugar and

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int sugarButtonPushCounter = 0;
int buttonState = 0;         // current state of the button
int decrementButtonState = 0;
int sugarButtonState = 0;
int sugarDecrementButtonState = 0;
int lastButtonState = 0;     // previous state of the button
int decrementLastButtonState = 0;
int sugarLastButtonState = 0;     // previous state of the button
int sugarDecrementLastButtonState = 0;
int startState = 0;
int delayTime;
int userSettingOneForCream;
int userSettingOneForSugar;
int userSettingTwoForCream;
int userSettingTwoForSugar;

void setup() {

  // put your setup code here, to run once:
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G

  pinMode(a_sugar, OUTPUT);  //A
  pinMode(b_sugar, OUTPUT);  //B
  pinMode(c_sugar, OUTPUT);  //C
  pinMode(d_sugar, OUTPUT);  //D
  pinMode(e_sugar, OUTPUT);  //E
  pinMode(f_sugar, OUTPUT);  //F
  pinMode(g_sugar, OUTPUT);  //G

  pinMode(pump, OUTPUT); //for pump

  servo1.attach(13);
  userProfile1.attachClick(SingleClickForProfileOne); //A single click will be used to ;pad a user profile 1
  userProfile1.attachLongPressStop(LongClickForProfileOne); //A long click will set the user profile 1
  userProfile2.attachClick(SingleClickForProfileTwo); //A single click will be used to ;pad a user profile 2
  userProfile2.attachLongPressStop(LongClickForProfileTwo); //A long click will set the user profile 2

  pinMode( buttonPin , INPUT_PULLUP );
  pinMode( decrementButtonPin, INPUT_PULLUP );
  pinMode( sugarButtonPin , INPUT_PULLUP );
  pinMode( sugarDecrementButtonPin, INPUT_PULLUP );
  pinMode( start, INPUT_PULLUP );

  Serial.begin(9600);

  userSettingOneForCream = EEPROM.read(0); //loads the using setting from ROM
  userSettingOneForSugar = EEPROM.read(1);
  userSettingTwoForCream = EEPROM.read(2); //loads the using setting from ROM
  userSettingTwoForSugar = EEPROM.read(3);


  displayDigit(buttonPushCounter);
  displaySugarDigit(sugarButtonPushCounter);
  //pumpTime(buttonPushCounter, sugarButtonPushCounter);
}

void loop() {
  userProfile1.tick();
  userProfile2.tick();
  delay(20);
  buttonState = digitalRead(buttonPin);
  decrementButtonState = digitalRead(decrementButtonPin);
  sugarButtonState = digitalRead(sugarButtonPin);
  sugarDecrementButtonState = digitalRead(sugarDecrementButtonPin);
  startState = digitalRead(start);

  if (buttonState == LOW) { // if the current state is HIGH then the button went from off to on:
    delay(250);
    buttonPushCounter++;
    if ( buttonPushCounter > 9)
      buttonPushCounter = 9;
    displayDigit(buttonPushCounter);
  }

  if (decrementButtonState == LOW) {
    delay(250);
    buttonPushCounter--;
    if ( buttonPushCounter < 0)
      buttonPushCounter = 0 ;
    displayDigit(buttonPushCounter);
  }

  if (sugarButtonState == LOW) { // if the current state is HIGH then the button went from off to on:
    delay(250);
    sugarButtonPushCounter++;
    if ( sugarButtonPushCounter > 9)
      sugarButtonPushCounter = 9;
    displaySugarDigit(sugarButtonPushCounter);
  }

  if (sugarDecrementButtonState == LOW) {
    delay(250);
    sugarButtonPushCounter--;
    if ( sugarButtonPushCounter < 0)
      sugarButtonPushCounter = 0 ;
    displaySugarDigit(sugarButtonPushCounter);
  }

  if (startState == LOW)
    pumpTime(buttonPushCounter, sugarButtonPushCounter);
}

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

void SingleClickForProfileOne()
{
  buttonPushCounter = EEPROM.read(0);
  sugarButtonPushCounter = EEPROM.read(1);
  displayDigit(userSettingOneForCream);
  displaySugarDigit(userSettingOneForSugar);
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
  displayDigit(userSettingTwoForCream);
  displaySugarDigit(userSettingTwoForSugar);
  delay(10);
}

void LongClickForProfileTwo()
{
  userSettingTwoForCream = buttonPushCounter;
  userSettingTwoForSugar = sugarButtonPushCounter;
  EEPROM.write(2, userSettingTwoForCream);
  EEPROM.write(3, userSettingTwoForSugar);
}

void displayDigit(int digit)
{
  switch (digit) //Case number will be the displayed digit
  {
    case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;
    case 1:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 4:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 5:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 6:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 9:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

  }
}
void displaySugarDigit(int digit)
{
  switch (digit) //Case number will be the displayed digit
  {
    case 0:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, HIGH);
      digitalWrite(e_sugar, HIGH);
      digitalWrite(f_sugar, HIGH);
      digitalWrite(g_sugar, LOW);
      break;
    case 1:
      digitalWrite(a_sugar, LOW);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, LOW);
      digitalWrite(e_sugar, LOW);
      digitalWrite(f_sugar, LOW);
      digitalWrite(g_sugar, LOW);
      break;
    case 2:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, LOW);
      digitalWrite(d_sugar, HIGH);
      digitalWrite(e_sugar, HIGH);
      digitalWrite(f_sugar, LOW);
      digitalWrite(g_sugar, HIGH);
      break;
    case 3:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, HIGH);
      digitalWrite(e_sugar, LOW);
      digitalWrite(f_sugar, LOW);
      digitalWrite(g_sugar, HIGH);
      break;
    case 4:
      digitalWrite(a_sugar, LOW);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, LOW);
      digitalWrite(e_sugar, LOW);
      digitalWrite(f_sugar, HIGH);
      digitalWrite(g_sugar, HIGH);
      break;
    case 5:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, LOW);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, HIGH);
      digitalWrite(e_sugar, LOW);
      digitalWrite(f_sugar, HIGH);
      digitalWrite(g_sugar, HIGH);
      break;
    case 6:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, LOW);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, HIGH);
      digitalWrite(e_sugar, HIGH);
      digitalWrite(f_sugar, HIGH);
      digitalWrite(g_sugar, HIGH);
      break;
    case 7:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, LOW);
      digitalWrite(e_sugar, LOW);
      digitalWrite(f_sugar, LOW);
      digitalWrite(g_sugar, LOW);
      break;
    case 8:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, HIGH);
      digitalWrite(e_sugar, HIGH);
      digitalWrite(f_sugar, HIGH);
      digitalWrite(g_sugar, HIGH);
      break;
    case 9:
      digitalWrite(a_sugar, HIGH);
      digitalWrite(b_sugar, HIGH);
      digitalWrite(c_sugar, HIGH);
      digitalWrite(d_sugar, HIGH);
      digitalWrite(e_sugar, LOW);
      digitalWrite(f_sugar, HIGH);
      digitalWrite(g_sugar, HIGH);
      break;

  }

}
