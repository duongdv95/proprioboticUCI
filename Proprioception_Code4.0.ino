#include <FiniteStateMachine.h>
#include <Keyboard.h>
#include <Servo.h>

//--------------------------Make variables--------------------------
int previousButtonState = HIGH;
int counter;
int randConfig;
int previousTwo[2];
int check;
int getRandom;
int deg1 = 140;
int deg2 = 55;

//--------------------------Make timer variables--------------------------

unsigned long previousMillis = 0;
const long interval = 7000;
unsigned long previousMillis2 = 0;
const long interval2 = 1000;
unsigned long previousMillis3 = 0;
const long interval3 = 50;


Servo myservo1;
Servo myservo2; 
void configOneUpdate(void);
void configTwoUpdate(void);
void configThreeUpdate(void);
void configFourUpdate(void);

State configOne(configOneUpdate);
State configTwo(configTwoUpdate);
State configThree(configThreeUpdate);
State configFour(configFourUpdate);
FSM proprioception;

//--------------------------Initialize the Arduino--------------------------

void setup() {
  myservo1.attach(3); // attach servo 1 to pin 2
  myservo2.attach(2); // attach servo 2 to pin 3
  pinMode(4, INPUT_PULLUP);
  Serial.begin(9600); 
  counter = -1;
  check = 0;
  proprioception.begin(configOne);
}

//--------------------------MAIN LOOPING FUNCTION--------------------------

void loop() {
//-----------------------------------------------------------------------------------------------------
  Keyboard.begin();
/*
 *Every 3 seconds, get a random configuration that does not repeat the last 2 random numbers
 *Every 1 second, print the current configuration to the Serial for testing purposes
 */
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    getRandom = randomFunction();
  }
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;
    Serial.println(getRandom);
  }
  proprioception.update(); // Update the current state
  if (currentMillis - previousMillis3 >= interval3) {
    previousMillis3 = currentMillis;
    Keyboard.releaseAll();
  }
//-----------------------------------------------------------------------------------------------------
  int buttonState = digitalRead(4);
  if (buttonState != previousButtonState) {
    Serial.print("Button pressed on configuration: ");
    Serial.println(getRandom);
    keyboard(getRandom); // Send random number configuration to keyboard
  }
//   save the current button state for comparison next time:
  previousButtonState = buttonState;
  Keyboard.end();
}

//--------------------------Random Configuration--------------------------

int randomFunction() {
/*
 * Counter starts at -1 and every interval, the counter increases by 1. When the Counter reaches 1,
 * the Counter resets to -1. This allows storing previous two random numbers in previousTwo[0] and
 * previousTwo[1]. This function also keeps generating a random number until it is no longer equal
 * to any numbers in previousTwo array.
 */
  counter ++;
  previousTwo[counter] = randConfig;
  while (check == 0) {
    randConfig = random(1,5);
    check = 1;
    for (int i = 0; i < 2; i++) {
      if (randConfig == previousTwo[i]) {
        check = 0;
      }
    }
  }
  if (counter == 1) {
    counter = -1;
  }
  check = 0;
  return randConfig;
}

//--------------------------FINITE STATE MACHINE FOR 4 CONFIGURATIONS START HERE--------------------------

void configOneUpdate() {
  /**
   * Neutral at 140 degrees
   */
  if (randConfig == 1) {
    myservo1.write(deg1);
    myservo2.write(deg1);
  }

  if (randConfig == 2) {
    proprioception.transitionTo(configTwo);
  }

  if (randConfig == 3) {
    proprioception.transitionTo(configThree);
  }

  if (randConfig == 4) {
    proprioception.transitionTo(configFour);
  }
  
}

void configTwoUpdate() {
  
  if (randConfig == 1) {
    proprioception.transitionTo(configOne);
  }

  if (randConfig == 2) {
    myservo1.write(deg2);
    myservo2.write(deg2);
    //Serial.println("configTwoUpdate works");
  }

  if (randConfig == 3) {
    proprioception.transitionTo(configThree);
  }

  if (randConfig == 4) {
    proprioception.transitionTo(configFour);
  }
  
}

void configThreeUpdate() {
  
  if (randConfig == 1) {
    proprioception.transitionTo(configOne);
  }

  if (randConfig == 2) {
    proprioception.transitionTo(configTwo);
  }

  if (randConfig == 3) {
    myservo1.write(deg1);
    myservo2.write(deg2);
    //Serial.println("configThreeUpdate works");
  }

  if (randConfig == 4) {
    proprioception.transitionTo(configFour);
  }
  
}

void configFourUpdate() {
  if (randConfig == 1) {
    proprioception.transitionTo(configOne);
  }

  if (randConfig == 2) {
    proprioception.transitionTo(configTwo);
  }

  if (randConfig == 3) {
    proprioception.transitionTo(configThree);
  }

  if (randConfig == 4) {
    myservo1.write(deg2);
    myservo2.write(deg1);
  }
  
}
void keyboard(int getRandom) {

  if (getRandom == 1) {
    Keyboard.press(KEY_DOWN_ARROW);
    Serial.println("Down Success");
  }
  else if (getRandom == 2) {
    Keyboard.press(KEY_UP_ARROW);
    Serial.println("Up Success");
  }
  else if (getRandom == 3) {
    Keyboard.press(KEY_RIGHT_ARROW);
    Serial.println("Right Success");
  }
  else if (getRandom == 4) {
    Keyboard.press(KEY_LEFT_ARROW);
    Serial.println("Left Success");
  }
}
//--------------------------FINITE STATE MACHINE FOR 4 CONFIGURATIONS ENDS HERE--------------------------
