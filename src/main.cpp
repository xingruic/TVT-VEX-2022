/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// MotorIntk            motor         11              
// MotorF1              motor         14              
// MotorF2              motor         15              
// MotorOut             motor         18              
// Pneu1                digital_out   A               
// Pneu2                digital_out   B               
// MotorLB              motor         20              
// MotorRB              motor         19              
// MotorRF              motor         1               
// MotorLF              motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "flywheel.h"
#include "autonomous.h"
#include "intake.h"
#include "expansion.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

void screenInit(){
  Brain.Screen.drawRectangle(0, 0, 240, 272, yellow);
  Brain.Screen.printAt(20,50,"Half1()");
  Brain.Screen.drawRectangle(0, 240, 200, 270, blue);
  Brain.Screen.printAt(260,50,"Half2()");
}


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/


// give lSpeed and rSpeed in percent
void drive(int lS, int rS){
  MotorLF.spin(forward,lS,percent);
  MotorLB.spin(forward,lS,percent);
  MotorRF.spin(forward,rS,percent);
  MotorRB.spin(forward,rS,percent);
}
bool pneu_rev=1;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Pneu1.set(true);
  Pneu2.set(true);

  MotorOut.setBrake(brake);
  MotorF1.setBrake(coast);
  MotorF2.setBrake(coast);

  MotorLF.setVelocity(60, percent);
  MotorLB.setVelocity(60, percent);
  MotorRF.setVelocity(60, percent);
  MotorRB.setVelocity(60, percent);

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

enum auton_mode{
  half2,
  half1,
  progsklz
}autonMode=progsklz;

void switchAlliance(){
  if(Brain.Screen.xPosition()<240){
    Brain.Screen.drawCircle(50, 200, 40, green);
    autonMode=half1;
  }
  else{
    autonMode=half2;
    Brain.Screen.drawCircle(50, 200, 40, blue);
  }
}

void autonomous(void) {
  MotorLF.setBrake(coast);
  MotorLB.setBrake(coast);
  MotorRF.setBrake(coast);
  MotorRB.setBrake(coast);
  Brain.resetTimer();
  switch(autonMode){
    case half2:
  auton::Half2();
    break;
    case half1:
  auton::Half1();
  auton::Half1Discs();
    break;
    case progsklz:
  auton::ProgSklz();
    break;
    default:
    break;
  }
  // MotorF1.spin(forward,100,percent);
  // MotorF2.spin(forward,100,percent);
  // auton::Half1();
  // auton::Half1Discs();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void singleRightDrive(){
  int LR = Controller1.Axis1.position();
  int FB = Controller1.Axis2.position();
  double lD = LR*0.7;
  double rD = -LR*0.7;
  lD+=FB;
  rD+=FB;
  if(lD>100) lD=100;
  if(rD>100) rD=100;
  if(lD<-100) lD=-100;
  if(rD<-100) rD=-100;

  drive(lD, rD);
}

void singleLeftDrive(){
  int LR = Controller1.Axis4.position();
  int FB = Controller1.Axis3.position();
  double lD = LR*0.5;
  double rD = -LR*0.5;
  lD+=FB;
  rD+=FB;
  if(lD>100) lD=100;
  if(rD>100) rD=100;
  if(lD<-100) lD=-100;
  if(rD<-100) rD=-100;

  drive(lD, rD);
}

void splitDrive(){
  int LR = Controller1.Axis1.position();
  int FB = Controller1.Axis3.position();
  double lD = LR*0.5;
  double rD = -LR*0.5;
  lD+=FB;
  rD+=FB;
  if(lD>100) lD=100;
  if(rD>100) rD=100;
  if(lD<-100) lD=-100;
  if(rD<-100) rD=-100;

  drive(lD, rD);
}

void tankDrive(){
  drive(Controller1.Axis3.position(),Controller1.Axis2.position());
}

void usercontrol(void) {
  MotorLF.setBrake(brake);
  MotorRF.setBrake(brake);
  MotorRB.setBrake(brake);
  MotorLB.setBrake(brake);
  
  int FWSpin=0;
  // User control code here, inside the loop

  int flySpeed=0;

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    splitDrive();
    
    if(Controller1.ButtonL1.pressing()) spinIntk(100);
    else if(Controller1.ButtonL2.pressing()) spinIntk(-50);
    else spinIntk(0);


    if(Controller1.ButtonX.pressing()) FWSpin=1;
    if(Controller1.ButtonR1.pressing()) FWSpin=2;
    if(Controller1.ButtonR2.pressing()) FWSpin=0;
    if(FWSpin==1){
      spinFly(flySpeed=100);
    }else if(FWSpin==2){
      spinFly(flySpeed=65);
    }else{
      MotorF1.spin(forward,0,percent);
      MotorF2.spin(forward,0,percent);
    }

    if(Controller1.ButtonA.pressing()) tripleFire(flySpeed);

    if(Controller1.ButtonRight.pressing() && Controller1.ButtonY.pressing()){
      expand();
    }

    wait(30, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();

  screenInit();

  Brain.Screen.pressed(switchAlliance);

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
