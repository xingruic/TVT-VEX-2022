#ifndef FLYWHEEL_H
#define FLYWHEEL_H
#include "vex.h"

using namespace vex;

void spinFly(int speed);
double getFlywheelSpeed(double target, double &OldError, double &TBHval, double &FWDrive);
#endif