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
// MotorLF              motor         11              
// MotorLB              motor         20              
// MotorRF              motor         3               
// MotorRB              motor         4               
// MotorIntk            motor         5               
// MotorF1              motor         6               
// MotorF2              motor         7               
// MotorOut             motor         8               
// Pneu1                digital_out   A               
// Pneu2                digital_out   B               
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

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Pneu1.set(true);
  Pneu2.set(true);

  MotorOut.setBrake(brake);

  MotorLF.setVelocity(50, percent);
  MotorLB.setVelocity(50, percent);
  MotorRF.setVelocity(50, percent);
  MotorRB.setVelocity(50, percent);

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

void autonomous(void) {

  // auton::Half2();

  auton::Half1();
  auton::Half1Discs();
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

void splitDrive(){
  int LR = Controller1.Axis1.position();
  int FB = Controller1.Axis3.position();
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

void tankDrive(){
  drive(Controller1.Axis3.position(),Controller1.Axis2.position());
}

void usercontrol(void) {
  
  int FWSpin=0;
  // User control code here, inside the loop

  Controller1.ButtonA.pressed(fireRing);

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
    else if(Controller1.ButtonL2.pressing()) spinIntk(-70);
    else spinIntk(0);

    if(Controller1.ButtonX.pressing()) FWSpin=1;
    if(Controller1.ButtonR1.pressing()) FWSpin=2;
    if(Controller1.ButtonR2.pressing()) FWSpin=0;
    if(FWSpin==1){
      spinFly(100);
    }else if(FWSpin==2){
      spinFly(75);
    }else{
      spinFly(0);
    }

    if(Controller1.ButtonRight.pressing()) Pneu1.set(false);

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

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
