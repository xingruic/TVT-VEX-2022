#include "flywheel.h"
#include "vex.h"

using namespace vex;

// give millivolts
void spinFlyVolts(const int &mVolts) {
  MotorF1.spin(fwd, mVolts, voltageUnits::mV);
  MotorF2.spin(fwd, mVolts, voltageUnits::mV);
}

// controls the flywheel speed. must be run constantly to work properly, so be
// careful when using it in auton.
void spinFly(int speed) {
  float vel = MotorF1.velocity(percent);
  float error = speed - vel;
  const float kp = 0.02;
  spinFlyVolts((speed + kp * error) * 120);
  Brain.Screen.printAt(30, 30, "flywheel speed: %.2f                  ",
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
  MotorOut.spin(fwd, 12000, voltageUnits::mV);
  wait(200, msec);
  MotorOut.spin(reverse, 12000, voltageUnits::mV);
  wait(300, msec);
  firing = false;
}

void tripleFire() {
  fireRing();
  wait(10, msec);
  fireRing();
  wait(10, msec);
  fireRing();
  wait(10, msec);
}