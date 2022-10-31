#ifndef FLYWHEEL_H
#define FLYWHEEL_H

void spinFly(int speed);
double getFlywheelSpeed(double target, double &OldError, double &TBHval, double &FWDrive);
void fireRing();

#endif