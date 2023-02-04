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
  float speed = 27.0;
  float accuracy = 0.2;
  MotorLB.setRotation(0, rev);
  while (fabs(error) > accuracy) {
    _drive(speed * error, speed * error);
    wait(10,msec);
    x = MotorLB.position(rev) * 3.14 * 3.25;
    error = target - x;
  }
  _drive(0,0);
}

void gyroSpin(float target){
  Gyro.setRotation(0.0, degrees);
  float kp = 1.5;
  float heading = 0.0;
  float error = target-heading;
  float speed = kp * error;
  float accuracy = 0.5;
  float bias = 1;
  int cnt=3;
  while (cnt>0) {
    if(fabs(error)<accuracy) cnt--;
    else cnt=3;
    speed = kp * error + bias * fabs(error) / error;
    _drive(speed, -speed);
    wait(5,msec);
    heading = Gyro.rotation(degrees);
    error = target - heading;
    Brain.Screen.printAt(1, 20, "heading = %.2f     ", heading);
  }
  _drive(0,0);
}

void auton::driveVolts(float lS, float rS){
  MotorLF.spin(forward,lS,voltageUnits::mV);
  MotorLB.spin(forward,lS,voltageUnits::mV);
  MotorRF.spin(forward,rS,voltageUnits::mV);
  MotorRB.spin(forward,rS,voltageUnits::mV);
}

void auton::Half1(){
  _spinFly(83);
  spinIntk(-40);
  wait(100,msec);
  driveVolts(3000, 3000);
  wait(550,msec);
  _drive(0,0);
  spinIntk(0);
  driveInch(-5);
  gyroSpin(-7);
  spinFlyFor(82, 1400);
  fireRing();
  spinFlyFor(82, 1400);
  fireRing();
  gyroSpin(-135);
  spinIntk(100);
  _spinFly(73);
  driveInch(23);
  wait(400,msec);
  driveInch(12);
  wait(400,msec);
  driveInch(12);
  wait(400,msec);
  gyroSpin(100);
  spinFlyFor(75, 200);
  fireRing();
  spinFlyFor(75, 1400);
  fireRing();
  spinFlyFor(75, 1400);
  fireRing();
  fireRing();
  Controller1.rumble("-");
}

void auton::Half2(){
  // _spinFly(100);
  // fireRing();
  // _spinFly(30);
  // fireRing();
  driveInch(17);
  _spinFly(80);
  gyroSpin(94);
  driveInch(4);
  spinIntk(-20);
  wait(100,msec);
  driveVolts(1000, 1000);
  wait(500,msec);
  spinIntk(0);
  driveInch(-4);
  gyroSpin(12.5);
  spinFlyFor(80, 500);
  fireRing();
  spinFlyFor(80, 1300);
  fireRing();
  _spinFly(72);
  gyroSpin(123.5);
  spinIntk(100);
  driveInch(50);
  wait(500,msec);
  driveInch(10);
  gyroSpin(-85);
  spinFlyFor(75, 400);
  fireRing();
  spinFlyFor(75, 1300);
  fireRing();
  spinFlyFor(75, 1300);
  fireRing();
  Controller1.rumble("-");
}

void auton::ProgSklz(){
  
}