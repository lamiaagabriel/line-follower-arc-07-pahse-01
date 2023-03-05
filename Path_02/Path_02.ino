// IR Sensor
#define LEFT_PIN 2
#define CENTER_PIN 3
#define RIGHT_PIN 4

// H-bridge Motors
#define ML_EN 6
#define ML_H 7
#define ML_L 8

#define MR_EN 9
#define MR_H 10
#define MR_L 11

// the speed is unlike, bcz of the acutal speed of motors are not the same at the same value.
#define ML_SPEED 85
#define MR_SPEED 65

// Counter for a specific action
int COUNTER = 0;

void setup() {
  // Set the IR pins as inputs
  pinMode(LEFT_PIN, INPUT);
  pinMode(CENTER_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);
  
  // Set the motor pins as outputs
  pinMode(ML_EN, OUTPUT); 
  pinMode(ML_H, OUTPUT);
  pinMode(ML_L, OUTPUT);
  
  pinMode(MR_EN, OUTPUT);
  pinMode(MR_H, OUTPUT);
  pinMode(MR_L, OUTPUT);
}


void loop() {
  if(COUNTER < 3) {
    Path();
  }
}

// -------------------------------- Path 02
void Path() {
  // Read the sensor values
  int isLeft = digitalRead(LEFT_PIN);
  int isCenter = digitalRead(CENTER_PIN);
  int isRight = digitalRead(RIGHT_PIN);

  if(isLeft && isCenter && isRight) { // All Black 1 1 1
    stopMotors();
    if(COUNTER == 0)
      cases(isLeft, isCenter, isRight);
    else 
      goForwardSkip(isLeft, isCenter, isRight);
      
  } else if(isLeft && isCenter && !isRight) { // Left-Center 1 1 0
    turnRight();
  } else if(isLeft && !isCenter && isRight) { // Left-Right 1 0 1
    goBackward();
  } else if(isLeft && !isCenter && !isRight) { // Left 1 0 0
    turnRight();
  } else if(!isLeft && isCenter && isRight) { // Center-Right 0 1 1
    turnLeft();
  } else if(!isLeft && isCenter && !isRight) { // Center 0 1 0
    goForward();
  } else if(!isLeft && !isCenter && isRight) { // Right 0 0 1
    turnLeft();
  } else if(!isLeft && !isCenter && !isRight) { // All White 0 0 0
    goBackward();
  }
}

void cases(int isLeft, int isCenter, int isRight) {
  switch(COUNTER) {
    case 0:
      for(int i = 0; i < 10; i++) {
        goBackward();
        delay(10);
      }
      turnCurveRight();
      COUNTER++;
      break;
    
    case 1:
      table(isLeft, isCenter, isRight);
      COUNTER++;
      break;

    case 2:
      COUNTER++;
      stopMotors();
      COUNTER++;
      break;
  }
}

void turnCurveRight() {
  for(int i = 0; i < 5; i++) {
    for(int i = 0; i < 6; i++) {
      turnRight();
      delay(10);
    }
    for(int i = 0; i < 13; i++) {
      goForward();
      delay(10);
    }
  }
}

void table(int isLeft, int isCenter, int isRight) {
  do {
    goForward();
    isLeft = digitalRead(LEFT_PIN);
    isCenter = digitalRead(CENTER_PIN);
    isRight = digitalRead(RIGHT_PIN);
  } while(isLeft && isCenter && isRight);
  
  stopMotors();
  delay(10000);
  goForward();
}
void goForwardExit(int isLeft, int isCenter, int isRight) { // Exit the big black shape
  do {
    goForward();
    isLeft = digitalRead(LEFT_PIN);
    isCenter = digitalRead(CENTER_PIN);
    isRight = digitalRead(RIGHT_PIN);
  } while(isLeft && isCenter && isRight);
}

void goForwardSkip(int isLeft, int isCenter, int isRight) { // To skip any 3 unwanted black read
  for(int i = 0; i < 30; i++) {
    goForward();
    delay(10);
  }
  isLeft = digitalRead(LEFT_PIN);
  isCenter = digitalRead(CENTER_PIN);
  isRight = digitalRead(RIGHT_PIN);
  
  if(isLeft && isCenter && isRight) // execute cases, if the 3 black is a case
    cases(isLeft, isCenter, isRight);
}


void goForward() {
    analogWrite(ML_EN, ML_SPEED);
    analogWrite(MR_EN, MR_SPEED);

    digitalWrite(ML_H, HIGH);
    digitalWrite(ML_L, LOW);

    digitalWrite(MR_H, HIGH);
    digitalWrite(MR_L, LOW);
}

void goBackward() {
    analogWrite(ML_EN, ML_SPEED + 10);
    analogWrite(MR_EN, MR_SPEED);
    
    digitalWrite(ML_H, LOW);
    digitalWrite(ML_L, HIGH);
    
    digitalWrite(MR_H, LOW);
    digitalWrite(MR_L, HIGH);
}
void turnLeft() {
    analogWrite(ML_EN, 0);
    analogWrite(MR_EN, MR_SPEED);
    
    digitalWrite(ML_H, LOW);
    digitalWrite(ML_L, LOW);
    
    digitalWrite(MR_H, HIGH);
    digitalWrite(MR_L, LOW);
}

void turnRight() {
    analogWrite(ML_EN, ML_SPEED);
    analogWrite(MR_EN, 0);

    digitalWrite(ML_H, HIGH);
    digitalWrite(ML_L, LOW);
    
    digitalWrite(MR_H, LOW);
    digitalWrite(MR_L, LOW);
}

void stopMotors() {
  for(int i = 0; i < 50; i++) {
    analogWrite(ML_EN, 0);
    analogWrite(MR_EN, 0);
    
    digitalWrite(ML_H, LOW);
    digitalWrite(ML_L, LOW);
   
    digitalWrite(MR_H, LOW);
    digitalWrite(MR_L, LOW);
    
    delay(10);
  }
}
