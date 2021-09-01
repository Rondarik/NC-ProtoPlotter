
#include <Stepper.h>

const int StepsPerRevolution = 2038;
int xPos;
int yPos;
int maxStepsX = 2038;
int maxStepsY = 2038;
Stepper xStepper(StepsPerRevolution, 8, 10, 9, 11);
Stepper yStepper(StepsPerRevolution, 4, 6, 5, 7);

int xInput = A0;
int yInput = A1;
int xSwitchPIN = 2;
int ySwitchPIN = 2;

void setup() {
  Serial.begin(9600);
  pinMode(xSwitchPIN, INPUT_PULLUP);

  searchZeroPos(xStepper, xSwitchPIN);
  xPos = 0;
  delay(1000);
  searchZeroPos(yStepper, ySwitchPIN);
  yPos = 0;

  Serial.println("Ursprung gesetzt.");
  Serial.println("(0;0)");
}

void loop() {
  
  int xValue = analogRead(xInput);
  int xSteps = calculateSteps(map(xValue, 0, 1023, 12, -12),maxStepsX, xPos);
   
  if (xSteps != 0) {
    xStepper.setSpeed(abs(xSteps/2));
  }
  
  xStepper.step(xSteps);
  xPos += xSteps;
  
  int yValue = analogRead(yInput);
  int ySteps = calculateSteps(map(yValue, 0, 1023, 12, -12),maxStepsY, yPos);
  
   if (ySteps != 0) {
    yStepper.setSpeed(abs(ySteps/2));
  }
  
  yStepper.step(ySteps);
  yPos += ySteps;
  
  if ((xSteps != 0)||(ySteps != 0)){
    Serial.print("(");
    Serial.print(xPos);   
    Serial.print(";");
    Serial.print(yPos);
    Serial.println(")");
  }
}

int calculateSteps(int value, int maxSteps, int pos) {
  int steps = 0;
  if (value < 0) {
    steps = -min(pos, -2*value);
  } else {
    steps = 2*value;
    if (pos + steps > maxSteps) {
      steps = maxSteps - pos;
    }
  }
  return steps;
}

int searchZeroPos(Stepper stepper, int switchPin) {
  int switchPressed = digitalRead(switchPin);
  
   while (switchPressed == 1) {
    stepper.setSpeed(12);
    stepper.step(24);
    switchPressed = digitalRead(switchPin);
  }
}
