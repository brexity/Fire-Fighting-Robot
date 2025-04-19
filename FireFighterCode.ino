#include <Servo.h>


#define enA 10     // Enable pin for Motor A
#define in1 8      // Motor A control pin 1
#define in2 9      // Motor A control pin 2
#define in3 6      // Motor B control pin 1
#define in4 7      // Motor B control pin 2
#define enB 5      // Enable pin for Motor B


#define ir_R 11     // Right IR sensor pin (digital)
#define ir_F A1    // Front IR sensor pin (analog)
#define ir_L A2    // Left IR sensor pin (analog)
#define servoPin A3  // Servo pin for the pump
#define pumpPin A4   // Pump control pin


int Speed = 255;  // Motor speed (PWM value)
int s1, s2, s3;   // Sensor readings


Servo servo;  // Servo object for controlling the pump


// Motor control functions
void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}


void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}


void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}


void turnLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}


void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


// Servo control to move pump to different positions
void setup() {
  Serial.begin(9600);  // Start serial communication for debugging
  pinMode(ir_R, INPUT);  // Right flame sensor (digital)
  pinMode(ir_F, INPUT);  // Front flame sensor (analog)
  pinMode(ir_L, INPUT);  // Left flame sensor (analog)
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);


  // Attach servo to pin
  servo.attach(servoPin);


  // Set initial motor speeds
  analogWrite(enA, Speed);
  analogWrite(enB, Speed);
  delay(500);
}


void loop() {
  // Read sensor values
  s1 = digitalRead(ir_R);  // Right IR sensor (digital)
  s2 = analogRead(ir_F);   // Front IR sensor (analog)
  s3 = analogRead(ir_L);   // Left IR sensor (analog)


  // Print sensor values to serial monitor for debugging
  Serial.print("Right: ");
  Serial.print(s1);
  Serial.print("\tFront: ");
  Serial.print(s2);
  Serial.print("\tLeft: ");
  Serial.println(s3);
  delay(100);


  // Check if fire is detected (sensor values below thresholds)
  if (s1 == LOW) {  // Right side sensor detects fire (LOW = flame detected)
    Stop();  // Stop the robot
    digitalWrite(pumpPin, HIGH);  // Activate the pump
    servo.write(40);  // Move the servo to spray position
    delay(1000);  // Spray for 1 second
    servo.write(90);  // Move the servo back to neutral position
    digitalWrite(pumpPin, LOW);  // Deactivate the pump
  }
  else if (s2 < 250) {  // Front sensor detects fire (analog)
    Stop();  // Stop the robot
    digitalWrite(pumpPin, HIGH);  // Activate the pump
    servo.write(90);  // Move the servo to spray position
    delay(1000);  // Spray for 1 second
    servo.write(90);  // Move the servo back to neutral position
    digitalWrite(pumpPin, LOW);  // Deactivate the pump
  }
  else if (s3 < 250) {  // Left side sensor detects fire (analog)
    Stop();  // Stop the robot
    digitalWrite(pumpPin, HIGH);  // Activate the pump
    servo.write(140);  // Move the servo to spray position
    delay(1000);  // Spray for 1 second
    servo.write(90);  // Move the servo back to neutral position
    digitalWrite(pumpPin, LOW);  // Deactivate the pump
  }  
  else if(s2>=251 && s2<=850){
    digitalWrite(pumpPin, 0);
    forward();
  }
  else if(s3>=251 && s3<=550){
    digitalWrite(pumpPin, 0);
    backward();
    delay(100);
    turnLeft();
    delay(200);
  }
 
  else {
    digitalWrite(pumpPin, LOW);  // Ensure pump is off
    Stop();  // Stop the robot if no fire is detected
 


  delay(10);  // Small delay for stability
  }
}
