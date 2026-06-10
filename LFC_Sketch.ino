// ======================================
// Ceemsys Technologies
// Contact - Ph: 9007986326
//           Email: info@ceensystechnologies.com
//           Website: https://ceemsys.com
// 
// scripts and support: https://github.com/MSupriya4223
// ======================================
// 3 SENSOR LINE FOLLOWER
// WITH OFFSET CALIBRATION
// + ULTRASONIC OBSTACLE STOP
// ======================================

// ---------- SENSOR PINS ----------
const int LEFT_SENSOR   = 2;
const int CENTER_SENSOR = 4;
const int RIGHT_SENSOR  = 3;

// ---------- ULTRASONIC SENSOR ----------
const int TRIG_PIN = 12;
const int ECHO_PIN = 11;

// ---------- MOTOR DRIVER PINS ----------
const int ENA = 5;   // RIGHT MOTOR SPEED
const int IN1 = 6;   // RIGHT MOTOR DIR1
const int IN2 = 7;   // RIGHT MOTOR DIR2

const int IN3 = 8;   // LEFT MOTOR DIR1
const int IN4 = 9;   // LEFT MOTOR DIR2
const int ENB = 10;  // LEFT MOTOR SPEED

// ======================================
// SPEED SETTINGS
// ======================================

const int BASE_SPEED = 90;

// Motor balancing
const int LEFT_MOTOR_OFFSET  = 0;
const int RIGHT_MOTOR_OFFSET = 10;

const int LEFT_SPEED  = BASE_SPEED + LEFT_MOTOR_OFFSET;
const int RIGHT_SPEED = BASE_SPEED + RIGHT_MOTOR_OFFSET;

// Turn speeds
const int SOFT_TURN_SPEED = BASE_SPEED - 10;
const int HARD_TURN_SPEED = BASE_SPEED;

// Obstacle distance
const int STOP_DISTANCE = 18; // cm

// Remember last direction
char lastDirection = 'F';

// ======================================

void setup() {

  pinMode(LEFT_SENSOR, INPUT);
  pinMode(CENTER_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

// ======================================

void loop() {

  // ==================================
  // ULTRASONIC CHECK
  // ==================================

  int distance = getDistance();

  // Stop if obstacle is closer than 18 cm
  if (distance > 0 && distance <= STOP_DISTANCE) {

    stopCar();
    return;
  }

  // ==================================
  // SENSOR READINGS
  // ==================================

  int leftState   = digitalRead(LEFT_SENSOR);
  int centerState = digitalRead(CENTER_SENSOR);
  int rightState  = digitalRead(RIGHT_SENSOR);

  // ==================================
  // SENSOR CONDITIONS
  // ==================================
  //
  // HIGH = BLACK LINE
  // LOW  = WHITE SURFACE
  //
  // L C R
  //
  // 0 1 0 -> Forward
  // 1 0 0 -> Left
  // 0 0 1 -> Right
  // 1 1 0 -> Sharp Left
  // 0 1 1 -> Sharp Right
  // 0 0 0 -> Line Lost
  // 1 1 1 -> Junction/Wide Line
  //
  // ==================================

  // CENTERED
  if (leftState == LOW &&
      centerState == HIGH &&
      rightState == LOW) {

    forward();
    lastDirection = 'F';
  }

  // SLIGHT LEFT
  else if (leftState == HIGH &&
           centerState == LOW &&
           rightState == LOW) {

    softLeft();
    lastDirection = 'L';
  }

  // SLIGHT RIGHT
  else if (leftState == LOW &&
           centerState == LOW &&
           rightState == HIGH) {

    softRight();
    lastDirection = 'R';
  }

  // SHARP LEFT
  else if (leftState == HIGH &&
           centerState == HIGH &&
           rightState == LOW) {

    hardLeft();
    lastDirection = 'L';
  }

  // SHARP RIGHT
  else if (leftState == LOW &&
           centerState == HIGH &&
           rightState == HIGH) {

    hardRight();
    lastDirection = 'R';
  }

  // ALL SENSORS ON BLACK
  // Wide line / Junction
  else if (leftState == HIGH &&
           centerState == HIGH &&
           rightState == HIGH) {

    forwardSlow();
  }

  // LINE LOST
  else {

    // Recover using last known direction

    if (lastDirection == 'L') {

      hardLeft();
    }

    else if (lastDirection == 'R') {

      hardRight();
    }

    else {

      forwardSlow();
    }
  }
}

// ======================================
// ULTRASONIC DISTANCE FUNCTION
// ======================================

int getDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 1000);

   if(duration == 0)
  {
    return 999;   // no obstacle detected
  }

  int distance = duration * 0.034 / 2;

  return distance;
}

// ======================================
// FORWARD
// ======================================

void forward() {

  analogWrite(ENA, RIGHT_SPEED);
  analogWrite(ENB, LEFT_SPEED);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ======================================
// FORWARD SLOW
// ======================================

void forwardSlow() {

  analogWrite(ENA, 30);
  analogWrite(ENB, 30);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ======================================
// SOFT LEFT
// ======================================

void softLeft() {

  analogWrite(ENA, RIGHT_SPEED);
  analogWrite(ENB, 15);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ======================================
// SOFT RIGHT
// ======================================

void softRight() {

  analogWrite(ENA, 15);
  analogWrite(ENB, LEFT_SPEED);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ======================================
// HARD LEFT
// ======================================

void hardLeft() {

  analogWrite(ENA, HARD_TURN_SPEED);
  analogWrite(ENB, HARD_TURN_SPEED);

  // Right motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Left motor backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ======================================
// HARD RIGHT
// ======================================

void hardRight() {

  analogWrite(ENA, HARD_TURN_SPEED);
  analogWrite(ENB, HARD_TURN_SPEED);

  // Right motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Left motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ======================================
// STOP
// ======================================

void stopCar() {

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}