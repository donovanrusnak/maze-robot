
//define and intialize sensors and constants

#define LEFT_MOTOR_A 9
#define LEFT_MOTOR_B 10
#define RIGHT_MOTOR_A 5
#define RIGHT_MOTOR_B 6
#define LEFT_MOTOR_POWER 200
#define RIGHT_MOTOR_POWER 200
#include <NewPing.h>

int left_sen = A0;
int center_sen = A1;
int right_sen = A2;

int val_left_sen = 0;
int val_center_sen = 0;
int val_right_sen = 0;

#define TRIGGER_FRONT 3
#define ECHO_FRONT 4

#define TRIGGER_LEFT 12
#define ECHO_LEFT 13

#define MAX_DISTANCE 200

NewPing frontSonar(TRIGGER_FRONT, ECHO_FRONT, MAX_DISTANCE);
NewPing leftSonar(TRIGGER_LEFT, ECHO_LEFT, MAX_DISTANCE);

#define LEFT_THRESHOLD 25
#define FRONT_THRESHOLD 25

#define centerThreshold 325
#define leftThreshold 290
#define rightThreshold 450

//setup input and output pins
void setup() {
  Serial.begin(9600);
  pinMode(left_sen, INPUT);
  pinMode(center_sen, INPUT);
  pinMode(right_sen, INPUT);
  pinMode(LEFT_MOTOR_A, OUTPUT);
  pinMode(LEFT_MOTOR_B, OUTPUT);
  pinMode(RIGHT_MOTOR_A, OUTPUT);
  pinMode(RIGHT_MOTOR_B, OUTPUT);
}

//infinite loop for reading in and responding to data
void loop(){

  //read in data from left and front distance sensors
  unsigned long leftDistance = leftSonar.ping_cm();
  unsigned long frontDistance = frontSonar.ping_cm();
  val_left_sen = analogRead(left_sen);
  val_right_sen = analogRead(right_sen);
  val_center_sen = analogRead(center_sen);

  //turn away from obstacle or wall if one is detected
  //if no obstacle is detected then follow line
  //if no line to follow do nothing
  if(leftDistance < LEFT_THRESHOLD || frontDistance < FRONT_THRESHOLD){
    if(leftDistance > LEFT_THRESHOLD)
      rotateLeft();
    else if(frontDistance > FRONT_THRESHOLD)
      forward();
    else
      rotateRight();
  } else{
    if(val_left_sen < leftThreshold){
      rotateRight();
      if (val_center_sen > centerThreshold)
        forward();
    } else if (val_right_sen < rightThreshold){
      rotateLeft();
      if (val_center_sen > centerThreshold)
        forward();
    } else if(val_left_sen > leftThreshold 
              && val_right_sen > rightThreshold
              && val_center_sen > centerThreshold){
      forward();
    } else if(val_left_sen > leftThreshold 
              && val_right_sen > rightThreshold
              && val_center_sen < centerThreshold){
        rotateLeft();
    }
  }

  //stop moving
  halt();
}

//move robot forward
void forward() {
  //LEFT MOTOR
  analogWrite(LEFT_MOTOR_A, LEFT_MOTOR_POWER);
  analogWrite(LEFT_MOTOR_B, LOW);
  //RIGHT MOTOR
  analogWrite(RIGHT_MOTOR_A, RIGHT_MOTOR_POWER);
  analogWrite(RIGHT_MOTOR_B, LOW);
  delay(50);
}

//move robot backwards
void back() {
  //LEFT MOTOR
  analogWrite(LEFT_MOTOR_A, LOW);
  analogWrite(LEFT_MOTOR_B, LEFT_MOTOR_POWER);
  //RIGHT MOTOR
  analogWrite(RIGHT_MOTOR_A, LOW);
  analogWrite(RIGHT_MOTOR_B, RIGHT_MOTOR_POWER);
  delay(50);
}

//stop robot
void halt() {
  //LEFT MOTOR
  analogWrite(LEFT_MOTOR_A, LOW);
  analogWrite(LEFT_MOTOR_B, LOW);
  //RIGHT MOTOR
  analogWrite(RIGHT_MOTOR_A, LOW);
  analogWrite(RIGHT_MOTOR_B, LOW);
  delay(500);
}

//turn robot right with left wheel as axis
void turnRight() {
  //LEFT MOTOR
  analogWrite(LEFT_MOTOR_A, LEFT_MOTOR_POWER);
  analogWrite(LEFT_MOTOR_B, LOW);
  //RIGHT MOTOR
  analogWrite(RIGHT_MOTOR_A, LOW);
  analogWrite(RIGHT_MOTOR_B, LOW);
  delay(50);
}

//turn robot left with right wheel as axis
void turnLeft() {
  //LEFT MOTOR
  analogWrite(LEFT_MOTOR_A, LOW);
  analogWrite(LEFT_MOTOR_B, LOW);
  //RIGHT MOTOR
  analogWrite(RIGHT_MOTOR_A, RIGHT_MOTOR_POWER);
  analogWrite(RIGHT_MOTOR_B, LOW);
  delay(50);
}

//turn robot right with center as axis
void rotateRight() {
  //LEFT MOTOR
  analogWrite(LEFT_MOTOR_A, LEFT_MOTOR_POWER);
  analogWrite(LEFT_MOTOR_B, LOW);
  //RIGHT MOTOR
  analogWrite(RIGHT_MOTOR_A, LOW);
  analogWrite(RIGHT_MOTOR_B, RIGHT_MOTOR_POWER);
  delay(50);
}

//turn robot left with center as axis
void rotateLeft() {
  //LEFT MOTOR
  analogWrite(LEFT_MOTOR_A, LOW);
  analogWrite(LEFT_MOTOR_B, LEFT_MOTOR_POWER);
  //RIGHT MOTOR
  analogWrite(RIGHT_MOTOR_A, RIGHT_MOTOR_POWER);
  analogWrite(RIGHT_MOTOR_B, LOW);
  delay(50);
}
