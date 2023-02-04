#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor MotorIntk = motor(PORT3, ratio18_1, true);
motor MotorF1 = motor(PORT12, ratio18_1, true);
motor MotorF2 = motor(PORT13, ratio18_1, false);
motor MotorOut = motor(PORT19, ratio18_1, false);
digital_out Pneu1 = digital_out(Brain.ThreeWirePort.A);
digital_out Pneu2 = digital_out(Brain.ThreeWirePort.B);
motor MotorLB = motor(PORT11, ratio18_1, false);
motor MotorRB = motor(PORT20, ratio18_1, true);
motor MotorRF = motor(PORT2, ratio18_1, true);
motor MotorLF = motor(PORT1, ratio18_1, false);
inertial Gyro = inertial(PORT18);
/*vex-vision-config:begin*/
signature Vision__RED_ = signature (1, 8385, 10519, 9452, -863, -487, -675, 4, 0);
signature Vision__BLUE_ = signature (2, -1927, -1293, -1610, 9067, 10601, 9834, 9.1, 0);
vision Vision = vision (PORT8, 50, Vision__RED_, Vision__BLUE_);
/*vex-vision-config:end*/

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