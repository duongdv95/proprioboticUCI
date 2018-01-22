int randNumber;
const int buttonPin=2;
int buttonState = 0;
unsigned long previousMillis = 0;
const long interval = 3000;
#include <Servo.h>
Servo myservo;
int pos = 0;

int LH_input() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {

    return 1;
  }
}

void setup () {
    Serial.begin(9600);
    pinMode(buttonPin, INPUT);
    myservo.attach(9);
}

void loop() {
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    randNumber = random(1,6);
    Serial.print(randNumber);
    if (randNumber == 1) {
      myservo.write(15);}
    if (randNumber == 2) {
      myservo.write(30);}
    if (randNumber == 3) {
      myservo.write(45);}
    if (randNumber == 4) {
      myservo.write(60);}
    if (randNumber == 5) {
      myservo.write(75);}
  }

  if (LH_input() == 1) {
    if (randNumber == 1) {
      Serial.print('up');
      //Send input "UP ARROW KEY to keyboard
    }
    if (randNumber == 2) {
      Serial.print('left');
      //Send input "LEFT ARROW KEY to keyboard
    }
    if (randNumber == 3) {
      Serial.print('down');
      //Send input "DOWN ARROW KEY to keyboard
    }
    if (randNumber == 4) {
      Serial.print('right');
      //Send input "RIGHT ARROW KEY to keyboard
    }

    
    }

   
  
}




