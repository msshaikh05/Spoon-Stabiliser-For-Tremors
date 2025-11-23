#include "arduino_secrets.h"

/*
  Arduino-Based Spoon Stabilizer for Tremor Assistance
  --------------------------------------
  Arduino UNO + MPU6050 + 2 Servos
*/

#include <Wire.h>
#include <Servo.h>

#define MPU 0x68

Servo servoRoll;
Servo servoPitch;

int16_t ax, ay, az;
int16_t gx, gy, gz;

float roll = 0, pitch = 0;
float rollAcc, pitchAcc;

float dt = 0.005;     // around 5ms loop time
float alpha = 0.98;   // complementary filter factor

void setup() {
  Wire.begin();
  Serial.begin(115200);

  // wake up MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  servoRoll.attach(9);
  servoPitch.attach(10);

  delay(200);
}

void loop() {
  readMPU();
  computeAngles();
  moveServos();
  delay(5);
}

// read raw accel + gyro
void readMPU() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);

  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();
  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();
}

// calculate pitch + roll   
void computeAngles() {
  float gyroRoll  = gx / 131.0;
  float gyroPitch = gy / 131.0;

  roll  += gyroRoll * dt;
  pitch += gyroPitch * dt;

  // accel angles
  rollAcc  = atan2(ay, az) * 180.0 / PI;
  pitchAcc = atan2(-ax, az) * 180.0 / PI;

  // blend gyro + accel
  roll  = alpha * roll  + (1 - alpha) * rollAcc;
  pitch = alpha * pitch + (1 - alpha) * pitchAcc;
}

// servo control
void moveServos() {
  int r = map(roll,  -45, 45,  0, 180);
  int p = map(pitch, -45, 45,  0, 180);

  r = constrain(r, 0, 180);
  p = constrain(p, 0, 180);

  servoRoll.write(r);
  servoPitch.write(p);
}
