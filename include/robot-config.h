using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor MotorIntk;
extern motor MotorF1;
extern motor MotorF2;
extern motor MotorOut;
extern digital_out Pneu1;
extern digital_out Pneu2;
extern motor MotorLB;
extern motor MotorRB;
extern motor MotorRF;
extern motor MotorLF;
extern inertial Gyro;
extern signature Vision__RED_;
extern signature Vision__BLUE_;
extern signature Vision__SIG_3;
extern signature Vision__SIG_4;
extern signature Vision__SIG_5;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern vision Vision;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );