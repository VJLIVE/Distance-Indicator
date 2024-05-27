#include <Servo.h>
#include <NewPing.h>

const int trigPin = 11;
const int echoPin = 12;
const int ServoPin = 10;
const int Buzzer = 9;
const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int LED4 = 5;
const int LED5 = 6;
const int LED6 = 7;
const int LED7 = 8;

long duration;
int distance;
NewPing sonar(trigPin, echoPin, 180);  // Max distance set to 180 cm
Servo servo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  servo.attach(ServoPin);
  
  Serial.begin(9600);
}

void loop() {
  // Send a 10 microsecond pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);  // Clear the trigger
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // Set the trigger high for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  // Clear the trigger
  // Read the echo pin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Distance calculation
  distance = (duration * 0.034) / 2;
  if(distance>180){
    distance=180;
  }
  // Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // LED Control
  digitalWrite(LED1, distance <= 30 ? HIGH : LOW);
  digitalWrite(LED2, distance > 30 && distance <= 60 ? HIGH : LOW);
  digitalWrite(LED3, distance > 60 && distance <= 90 ? HIGH : LOW);
  digitalWrite(LED4, distance > 90 && distance <= 120 ? HIGH : LOW);
  digitalWrite(LED5, distance > 120 && distance <= 150 ? HIGH : LOW);
  digitalWrite(LED6, distance > 150 && distance < 180 ? HIGH : LOW);
  digitalWrite(LED7, distance == 180 ? HIGH : LOW);

  // Servo Motor Control
  int angle = map(distance, 0, 180, 0, 180);
  servo.write(angle);

  // Buzzer Control
  digitalWrite(Buzzer, distance <= 30 ? HIGH : LOW);

  // Small delay to avoid flooding the sensor
  delay(2000);
}
