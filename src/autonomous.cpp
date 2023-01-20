#include "autonomous.h"
#include "intake.h"
#include "flywheel.h"
#include "vex.h"

using namespace vex;

void _spinFly(int speed){
  MotorF1.spin(forward,speed,percent);
  MotorF2.spin(forward,speed,percent);
}

void spinFlyFor(int speed,int msecs){
  double delay=10;
  for(int i=0; i<msecs/delay; i++){
    spinFly(speed);
    wait(delay,msec);
  }
}

void setVel(int vel){
  MotorLF.setVelocity(vel, percent);
  MotorLB.setVelocity(vel, percent);
  MotorRF.setVelocity(vel, percent);
  MotorRB.setVelocity(vel, percent);
}

void _drive(int lS, int rS){
  MotorLF.spin(forward,lS,percent);
  MotorLB.spin(forward,lS,percent);
  MotorRF.spin(forward,rS,percent);
  MotorRB.spin(forward,rS,percent);
}

void driveInch(float target){
  float x = 0.0;
  float error = target - x;
  float speed = 50.0;
  float accuracy = 0.2;
  MotorLB.setRotation(0, rev);
  while (fabs(error) > accuracy) {
    _drive(speed * fabs(error) / error, speed * fabs(error) / error);
    wait(10,msec);
    x = MotorLB.position(rev) * 3.14 * 3.25;
    error = target - x;
  }
  _drive(0,0);
}

void gyroSpin(float target){
  Gyro.setRotation(0.0, degrees);
  float kp = 1.0;
  float heading = 0.0;
  float error = target - heading;
  float speed = kp * error;
  float accuracy = 0.5;
  float bias = 1;
  while (fabs(error) > accuracy) {
    speed = kp * error + bias * fabs(error) / error;
    _drive(speed, -speed);
    wait(5,msec);
    heading = Gyro.rotation(degrees);
    error = target - heading;
    Brain.Screen.printAt(1, 20, "heading = %.2f  ", heading);
  }
  _drive(0,0);
}

void auton::driveVolts(float lS, float rS){
  MotorLF.spin(forward,lS,voltageUnits::mV);
  MotorLB.spin(forward,lS,voltageUnits::mV);
  MotorRF.spin(forward,rS,voltageUnits::mV);
  MotorRB.spin(forward,rS,voltageUnits::mV);
}

void auton::Half1Discs(){
  // driveInch(-5);
  // gyroSpin(-135);
  // spinIntk(100);
  // driveInch(15);
  // wait(2000,msec);
  driveInch(-5);
  gyroSpin(-12);
  spinFlyFor(87,3200);
  fireRing();
  spinFlyFor(87,1000);
  fireRing();
  _spinFly(0);
  gyroSpin(-125);
  driveInch(23);
  spinIntk(100);
  wait(500,msec);
  driveInch(-5);
  wait(1.5,sec);
  driveInch(10);
  wait(1.5,sec);
  driveInch(5);
  gyroSpin(90);

  Controller1.rumble("-");
}

void auton::Half1(){
  spinIntk(-40);
  wait(100,msec);
  driveVolts(3000, 3000);
  wait(550,msec);
  _drive(0,0);
  spinIntk(0);
}

void auton::Half2(){
  driveInch(17);
  // wait(200,msec);
  gyroSpin(90);
  // wait(200,msec);
  driveInch(3);
  spinIntk(-40);
  wait(100,msec);
  driveVolts(100, 100);
  _spinFly(86);
  wait(550,msec);
  _drive(0,0);
  spinIntk(0);
  driveInch(-4);
  // wait(200,msec);
  gyroSpin(2.5);
  spinFlyFor(84,1000);
  fireRing();
  spinFlyFor(84,1000);
  fireRing();
  _spinFly(0);
  gyroSpin(125);
  spinIntk(100);
  // wait(200,msec);
  driveInch(75);
  // wait(200,msec);
  _spinFly(80);
  driveInch(-10);
  // wait(200,msec);
  gyroSpin(-97);
  spinFlyFor(80,1000);
  fireRing();
  spinFlyFor(83,1000);
  fireRing();
  spinFlyFor(83,1000);
  fireRing();
  spinFly(0);
  Controller1.rumble("-");
}

void auton::ProgSklz(){
  
}