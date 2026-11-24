
#define IN1 A8
#define IN2 A9
#define IN3 A10
#define IN4 A11


// Define 7-segment display pins
const int segA = 5;
const int segB = 6;
const int segC = 7;
const int segD = 8;
const int segE = 9;
const int segF = 10;
const int segG = 11;


// Delay time between steps (lower value means faster speed)
int delayTime = 1; // Adjust this value for speed


// 7-segment digit encoding (0-3)
const byte digitCodes[4][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
};


const int irSensor1Pin = 2;  // Sensor for Floor 1
const int irSensor2Pin = 3;  // Sensor for Floor 2
const int irSensor3Pin = 4;  // Sensor for Floor 3


// Variable to track the current position of the lift
int currentFloor = 1;
int targetFloor = 0;


// Variables to store requests for each floor
bool requestFloor1 = false;
bool requestFloor2 = false;
bool requestFloor3 = false;


void setup() {
  // Define motor pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);


  // Set up button and IR sensor pins
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(irSensor1Pin, INPUT);
  pinMode(irSensor2Pin, INPUT);
  pinMode(irSensor3Pin, INPUT);
 
  // Initialize the display
  updateDisplay(currentFloor);
}


void loop() {
  // Check button presses for floor requests
  if (digitalRead(A0) == LOW && currentFloor != 1) {
    requestFloor1 = true;
  }
  if (digitalRead(A1) == LOW && currentFloor != 2) {
    requestFloor2 = true;
  }
  if (digitalRead(A2) == LOW && currentFloor != 3) {
    requestFloor3 = true;
  }


  // If there is no target floor set, find the next target based on the requests
  if (targetFloor == 0) {
    targetFloor = getNextTarget();
  }


  // If a target floor is set, move the lift
  if (targetFloor != 0) {
    moveToFloor(targetFloor);
  }


  delay(100);  // Small delay to debounce button press
}


void moveToFloor(int target) {
  // Determine the number of steps needed to reach the target floor
  int steps = (abs(target - currentFloor) == 1) ? 1024 : 2048; // 1024 steps for 1 floor, 2048 for 2 floors


  if (target < currentFloor) {
    // Move down
    for (int i = 0; i < steps; i++) {
      stepMotor(-1);  // Reverse direction for moving down
    }
  } else if (target > currentFloor) {
    // Move up
    for (int i = 0; i < steps; i++) {
      stepMotor(1);  // Forward direction for moving up
    }
  }


  // Recheck the IR sensor just before stopping
  if (checkFloorConditions(target)) {
    currentFloor = target;
    updateDisplay(currentFloor); // Update display
  } else {
    targetFloor = getNextTarget(); // If no object is detected, move to the next target
  }


  clearFloorRequest(target);
  targetFloor = 0;  // Reset target floor after reaching it
}


int getNextTarget() {
  if (currentFloor == 1) {
    if (requestFloor2 && digitalRead(irSensor2Pin) == LOW) return 2;
    if (requestFloor3 && digitalRead(irSensor3Pin) == LOW) return 3;
  } else if (currentFloor == 2) {
    if (requestFloor1 && digitalRead(irSensor1Pin) == LOW) return 1;
    if (requestFloor3 && digitalRead(irSensor3Pin) == LOW) return 3;
  } else if (currentFloor == 3) {
    if (requestFloor2 && digitalRead(irSensor2Pin) == LOW) return 2;
    if (requestFloor1 && digitalRead(irSensor1Pin) == LOW) return 1;
  }
  return 0;  // No valid target found
}


bool checkFloorConditions(int target) {
  if (target == 1 && requestFloor1 && digitalRead(irSensor1Pin) == LOW) {
    return true;
  }
  if (target == 2 && requestFloor2 && digitalRead(irSensor2Pin) == LOW) {
    return true;
  }
  if (target == 3 && requestFloor3 && digitalRead(irSensor3Pin) == LOW) {
    return true;
  }
  return false;
}


void clearFloorRequest(int floor) {
  if (floor == 1) requestFloor1 = false;
  if (floor == 2) requestFloor2 = false;
  if (floor == 3) requestFloor3 = false;
}


void updateDisplay(int floor) {
  for (int i = 0; i < 7; i++) {
    pinMode(segA + i, OUTPUT);
    digitalWrite(segA + i, digitCodes[floor][i]);
  }
}


void stepMotor(int direction) {
  if (direction > 0) {
    // Forward half-step sequence
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);  delayMicroseconds(delayTime * 1000);
    digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH); digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);  delayMicroseconds(delayTime * 1000);
    digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);  delayMicroseconds(delayTime * 1000);
    digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  delayMicroseconds(delayTime * 1000);
    digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  delayMicroseconds(delayTime * 1000);
    digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);  digitalWrite(IN3, HIGH); digitalWrite(IN4, HIGH); delayMicroseconds(delayTime * 1000);
    digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); delayMicroseconds(delayTime * 1000);
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); delayMicroseconds(delayTime * 1000);
  } else {
    // Reverse half-step sequence
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); delayMicroseconds(delayTime * 1000);
    digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); delayMicroseconds(delayTime * 1000);
    digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);  digitalWrite(IN3, HIGH); digitalWrite(IN4, HIGH); delayMicroseconds(delayTime * 1000);
    digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  delayMicroseconds(delayTime * 1000);
    digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  delayMicroseconds(delayTime * 1000);
    digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);  delayMicroseconds(delayTime * 1000);
    digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH); digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);  delayMicroseconds(delayTime * 1000);
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);  delayMicroseconds(delayTime * 1000);
  }
}
