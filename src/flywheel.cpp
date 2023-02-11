#include "flywheel.h"
#include "vex.h"

using namespace vex;

int flyTarget=0;

void setFlyTarget(int s){
  flyTarget=s;
}

int getFlyTarget(){
  return flyTarget;
}

// give millivolts
void spinFlyVolts(const int &mVolts) {
  MotorF1.spin(fwd, mVolts, voltageUnits::mV);
  MotorF2.spin(fwd, mVolts, voltageUnits::mV);
}

// int prevSpeed=0;

// controls the flywheel speed. must be run constantly to work properly, so be
// careful when using it in auton.
void spinFly(int speed) {
  // if(speed==0&&prevSpeed!=0){
  //   MotorF1.spin(fwd,0,percent);
  //   MotorF2.spin(fwd,0,percent);
  // }
  // prevSpeed=speed;
  float vel = MotorF1.velocity(percent);
  float error = speed - vel;

  if(speed==0) error=0;

  float kp = 0.02;

  if(error>20) error=1000;

  spinFlyVolts(fmax(-100,fmin(100,speed + kp * error)) * 120);
  Brain.Screen.printAt(30, 30, "flywheel speed: %.2f     ",
                       MotorF2.velocity(percent));
}

void spinFlyForMsec(int speed, int msecs) {
  for (int i = 0; i < msecs / 20; i++) {
    spinFly(speed);
    wait(20, msec);
  }
}

// fire ring
// void fireRing(){
//   MotorOut.spin(forward, 100, percent);
//   wait(100, msec);
//   MotorOut.spin(reverse, 100, percent);
//   wait(220, msec);
//   MotorOut.spin(forward, 0, percent);
// }

bool firing = false;
void fireRing() {
  if (firing)
    return;
  firing = true;
  MotorOut.resetPosition();
  MotorOut.spin(fwd, 12000, voltageUnits::mV);
  while(MotorOut.position(rev)<0.18) wait(10,msec);
  MotorOut.spin(reverse, 12000, voltageUnits::mV);
  wait(200, msec);
  MotorOut.spin(reverse,0,voltageUnits::mV);
  firing = false;
}

int flyControl(){
  while(1){
    spinFly(flyTarget);
    wait(20,msec);
  }
  return 0;
}