#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor MotorLF = motor(PORT1, ratio18_1, false);
motor MotorLB = motor(PORT2, ratio18_1, true);
motor MotorRF = motor(PORT3, ratio18_1, true);
motor MotorRB = motor(PORT4, ratio18_1, false);
motor MotorIntk = motor(PORT5, ratio18_1, true);
motor MotorF1 = motor(PORT6, ratio18_1, false);
motor MotorF2 = motor(PORT7, ratio18_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}