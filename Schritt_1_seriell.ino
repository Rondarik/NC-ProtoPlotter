
#include <Stepper.h>


int calculateSteps(int speed);

const int StepsPerRevolution = 2038;
int stepCounter = 0;
int maxSteps = 300;
Stepper myStepper(StepsPerRevolution, 8, 10, 9, 11);

int myTeiler = 1024/24;

int xInput = A0;
int yInput = A1;
int Switch = 7;


void setup() {
  Serial.begin(9600);
  pinMode(Switch, INPUT_PULLUP);
  stepCounter = 0; 
}

void loop() {
  
  int xValue = analogRead(xInput);
  int xValuehalbe = (xValue - 512);
  int mySpeed = map(xValue, 0, 1023, -12, 12);

  Serial.print("speed: ");
  Serial.println(mySpeed);
  // mySpeed = abs(xValuehalbe / myTeiler);
  if (mySpeed != 0) {
    myStepper.setSpeed(abs(mySpeed));
  }
  
//  Serial.println(mySpeed);
//  Serial.println(xValuehalbe);

  int steps = calculateSteps(mySpeed);
  myStepper.step(steps);
  
  Serial.print("steps: ");
  Serial.println(steps);
  stepCounter += steps;
  /*
    if ((xValuehalbe > 25) && (stepCounter <= maxSteps)) {
      if (stepCounter <= (maxSteps-mySpeed*2)) {
        myStepper.step(mySpeed*2);
        stepCounter += (mySpeed*2);
      } else {
        myStepper.step(maxSteps-stepCounter);
        stepCounter += (maxSteps-stepCounter);
      }
    } else if ((xValuehalbe < -25) && (stepCounter >= 0)) {
      if (stepCounter >= mySpeed*2) {
        myStepper.step(-mySpeed*2);
        stepCounter -= (mySpeed*2);
      } else {
        myStepper.step(-stepCounter);    
        stepCounter -= (stepCounter);
      }
    } 
    */
    Serial.print("position: ");
  Serial.println(stepCounter);

 
/*  bool buttonPressed = digitalRead(Switch) == LOW;
  if (buttonPressed) {
    Serial.println("Button pressed");
  }
*/

String direction = speed < 0
? "left"
: "right";
   
}

int calculateSteps(int speed) {
  int steps = 0;
  if (speed < 0) {
    steps = -min(stepCounter, -2*speed);
  } else {
    steps = 2*speed;
    if (stepCounter + steps > maxSteps) {
      steps = maxSteps - stepCounter;
    }
  }
  return steps;
}
