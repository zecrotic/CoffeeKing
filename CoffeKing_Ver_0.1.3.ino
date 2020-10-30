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
#include <HX711_ADC.h> // used for the weight sensors

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
const int start = 34; //Button to start the process of adding cream and sugar

const int HX711_dout = 4; //mcu > HX711 dout pin
const int HX711_sck = 5; //mcu > HX711 sck pin

const int redLedPinForSugarSensor = 8;
const int greenLedPinForSugarSensor = 9;
const int blueLedPinForSugarSensor = 10;



// Variables that will change:
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
int loopCounter = 0;


Servo servo1; //Servo for sugar dispenser
OneButton userProfile1(A6, true); //Attches the user profile 1 button to pin A6
OneButton userProfile2(A7, true); //Attches the user profile 2 button to pin A7
HX711_ADC LoadCell(HX711_dout, HX711_sck); //HX711 constructor for sugar weight sensor

const int calVal_eepromAdress = 18; //used for weight sensor
long t; //used for weight sensor

void setup() {
  /*
     SETUP PRINT FOR WEIGHT SENSOR
  */
  Serial.begin(9600); delay(10);
  Serial.println();
  Serial.println("Starting...");

  LoadCell.begin();
  float calibrationValue; // calibration value (see example file "Calibration.ino")
  calibrationValue = 85; // uncomment this if you want to set the calibration value in the sketch
  /*
    #if defined(ESP8266)|| defined(ESP32)
    //EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
    #endif
    //EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom
  */
  long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    Serial.println("Startup is complete");
  }
  /*

  */

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

  pinMode(redLedPinForSugarSensor, OUTPUT);
  pinMode(greenLedPinForSugarSensor, OUTPUT);
  pinMode(blueLedPinForSugarSensor, OUTPUT);

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

  userSettingOneForCream = EEPROM.read(0); //loads the using setting from ROM
  userSettingOneForSugar = EEPROM.read(1);
  userSettingTwoForCream = EEPROM.read(2); //loads the using setting from ROM
  userSettingTwoForSugar = EEPROM.read(3);


  displayDigit(buttonPushCounter);
  displaySugarDigit(sugarButtonPushCounter);
}

void loop() {
  float i; // value of the weight sensor
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



  /*
     START OF COPY AND PAST FROM Read_1x_load_cell
  */

  static boolean newDataReady = 0;
  const int serialPrintInterval = 100; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      i = LoadCell.getData();
      Serial.print("Load_cell output val: ");
      Serial.println(i);
      newDataReady = 0;
      t = millis();
      if (loopCounter < 100) {
        if (i > 200)
          setColor(0, 100, 0);
        else if (i > 50 && i < 200)
          setColor(160, 230, 0); // Yellow Color
        else
          setColor(255, 0, 0);
      }
      else
        setColor(0, 0, 0);
    }
  }

  // receive command from serial terminal, send 't' to initiate tare operation:
  if (Serial.available() > 0) {
    //float i;
    char inByte = Serial.read();
    if (inByte == 't') LoadCell.tareNoDelay();
  }

  // check if last tare operation is complete:
  if (LoadCell.getTareStatus() == true) {
    Serial.println("Tare complete");
  }
  /*
    END OF COPY AND PAST FROM Read_1x_load_cell
  */
  /*
  loopCounter++;
  if (loopCounter > 100) {
    displayDigit(10); // turns cream digit off
    displaySugarDigit(10);
  }
  //serial.Println("loop Counter: ");
*/
  if (startState == LOW && i > 50)
    pumpTime(buttonPushCounter, sugarButtonPushCounter);
  else if (startState == LOW && i < 50) {
    for (int j = 0; j < 4; j++) {
      setColor(255, 0, 0);
      delay(500);
      setColor(0, 0, 0);
      delay(500);
    }
  }
}
