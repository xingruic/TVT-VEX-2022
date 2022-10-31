#include "intake.h"
#include "vex.h"

using namespace vex;

// give speed in percent
void spinIntk(int speed){
  MotorIntk.spin(forward, speed, percent);
}
