#include "flywheel.h"

using namespace vex;

void spinFly(int speed){
  MotorF1.spin(forward, speed, percent);
  MotorF2.spin(forward, speed, percent);
}
double getFlywheelSpeed(double target, double &OldError, double &TBHval, double &FWDrive) {
  double kI = .05;
  double speed = MotorF1.velocity(percent);
  double error = target - speed;
  double fwDrive = FWDrive + kI * error;
  // Keep drive between 0 to 100%
  if (fwDrive > 100)
    fwDrive = 100;
  if (fwDrive < 0)
    fwDrive = 0;
  // Check for zero crossing
  if (error * OldError < 0) {
    fwDrive = 0.6 * (fwDrive + TBHval);
    TBHval = fwDrive;
  }

  FWDrive = fwDrive;
  OldError = error;

  return fwDrive;
}