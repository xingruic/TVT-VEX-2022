using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor MotorLF;
extern motor MotorLB;
extern motor MotorRF;
extern motor MotorRB;
extern motor MotorIntk;
extern motor MotorF1;
extern motor MotorF2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );