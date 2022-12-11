#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor MotorIntk = motor(PORT11, ratio18_1, true);
motor MotorF1 = motor(PORT14, ratio18_1, false);
motor MotorF2 = motor(PORT15, ratio18_1, true);
motor MotorOut = motor(PORT18, ratio18_1, false);
digital_out Pneu1 = digital_out(Brain.ThreeWirePort.A);
digital_out Pneu2 = digital_out(Brain.ThreeWirePort.B);
motor MotorLB = motor(PORT20, ratio18_1, false);
motor MotorRB = motor(PORT19, ratio18_1, true);
motor MotorRF = motor(PORT1, ratio18_1, true);
motor MotorLF = motor(PORT2, ratio18_1, false);

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