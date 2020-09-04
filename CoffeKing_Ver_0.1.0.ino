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
Servo servo1;     //Servo for sugar dispenser
const int a = 8;  //For displaying segment "a"
const int b = 9;  //For displaying segment "b"
const int c = 4;  //For displaying segment "c"
const int d = 5;  //For displaying segment "d"
const int e = 6;  //For displaying segment "e"
const int f = 2;  //For displaying segment "f"
const int g = 3;  //For displaying segment "g"
const int pump = 7;  //Pump for cream
const int stirMotor = 22;

bool bPress = false;
const int buttonPin = 10; //Attached to the button that increments the count
const int decrementButtonPin = 11; //Attached to the button to decrement the count
const int start = 12; //Button to start the process of adding cream and sugar and

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int decrementButtonState = 0;
int lastButtonState = 0;     // previous state of the button
int decrementLastButtonState = 0;
int startState = 0;
int delayTime = 1;

void setup() {

  // put your setup code here, to run once:
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G
  pinMode(pump, OUTPUT); //for pump

  servo1.attach(13);
  pinMode( buttonPin , INPUT_PULLUP );
  pinMode( decrementButtonPin, INPUT_PULLUP );
  pinMode( start, INPUT_PULLUP );
  Serial.begin(9600);
  displayDigit(buttonPushCounter);
  pumpTime(delayTime);
}

void loop() {
  //digitalWrite(pump, LOW);
  buttonState = digitalRead(buttonPin);
  decrementButtonState = digitalRead(decrementButtonPin);
  startState = digitalRead(start);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == LOW) {
      // if the current state is HIGH then the button went from off to on:
      bPress = true;
      buttonPushCounter++;
      //digitalWrite(pump, HIGH);
      if ( buttonPushCounter > 9)
        buttonPushCounter = 9 ;
      Serial.println("on");
      //delay(250);
      //digitalWrite(pump, LOW);

    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
  }
  //buttonState = decrementButtonState;
  if (decrementButtonState != decrementLastButtonState) {
    if (decrementButtonState == LOW) {
      // if the current state is HIGH then the button went from off to on:
      bPress = true;
      buttonPushCounter--;
      if ( buttonPushCounter < 0) buttonPushCounter = 0 ;
      Serial.println("on");

    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
  }
  // Delay a little bit to avoid bouncing
  delay(50);
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
  decrementLastButtonState = decrementButtonState;

  if ( bPress )
    displayDigit(buttonPushCounter);
  if (startState == LOW)
    pumpTime(buttonPushCounter);
}

void pumpTime(int digit) {
  if (startState == LOW) {
    int time = digit * 100;
    digitalWrite(pump, HIGH);
    delay(time);
    digitalWrite(pump, LOW);
    for (int numOfSugar = 0; numOfSugar < digit; numOfSugar += 1)
    {
      servo1.write(180);
      delay(1000); // The delays have to be fairly long here
      servo1.write(-180);
      delay(1000); // The delays have to be fairly long here
    }
    digitalWrite(stirMotor, HIGH);
    delay(500);
    digitalWrite(stirMotor, LOW);
  }
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
