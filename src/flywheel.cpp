#include "flywheel.h"
#include "vex.h"

using namespace vex;

// give millivolts
void spinFlyVolts(const int &mVolts){
  MotorF1.spin(fwd,mVolts,voltageUnits::mV);
  MotorF2.spin(fwd,mVolts,voltageUnits::mV);
}

// controls the flywheel speed. must be run constantly to work properly, so be careful when using it in auton.
void spinFly(int speed){
  float vel=MotorF1.velocity(percent);
  float error=speed-vel;
  const float kp=0.025;
  spinFlyVolts((speed+kp*fmax(0,error))*120);
  Brain.Screen.printAt(30,30,"flywheel speed: %.2f                  ", MotorF2.velocity(percent));
}

int spinFlyGlobal(void *speed){
  while(true){
    spinFly(*(int*)speed);
    wait(30,msec);
  }
  return 0;
}

// fire ring
// void fireRing(){
//   MotorOut.spin(forward, 100, percent);
//   wait(100, msec);
//   MotorOut.spin(reverse, 100, percent);
//   wait(220, msec);
//   MotorOut.spin(forward, 0, percent);
// }

// fire ring using pneumatic
void fireRing(){
  MotorOut.spin(fwd,12000,voltageUnits::mV);
  wait(130,msec);
  MotorOut.spin(reverse,12000,voltageUnits::mV);
  wait(200,msec);
}

void tripleFire(){
  fireRing();
  wait(10,msec);
  fireRing();
  wait(10,msec);
  fireRing();
  wait(10,msec);
}