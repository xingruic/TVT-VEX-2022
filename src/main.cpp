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
// MotorIntk            motor         3               
// MotorF1              motor         12              
// MotorF2              motor         13              
// MotorOut             motor         19              
// Pneu1                digital_out   A               
// Pneu2                digital_out   B               
// MotorLB              motor         11              
// MotorRB              motor         20              
// MotorRF              motor         2               
// MotorLF              motor         1               
// Gyro                 inertial      18              
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

  // Competition.bStopAllTasksBetweenModes=true;

  Pneu1.set(false);
  Pneu2.set(false);

  MotorOut.setBrake(hold);
  MotorF1.setBrake(coast);
  MotorF2.setBrake(coast);

  MotorLF.setVelocity(60, percent);
  MotorLB.setVelocity(60, percent);
  MotorRF.setVelocity(60, percent);
  MotorRB.setVelocity(60, percent);
}

enum auton_mode{
  half2,
  half1,
  progsklz
}autonMode=half1;

void switchAlliance(){
  if(Brain.Screen.xPosition()<240){
    Brain.Screen.drawCircle(100, 200, 40, green);
    autonMode=half1;
  }
  else{
    autonMode=half2;
    Brain.Screen.drawCircle(100, 200, 40, blue);
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
  Brain.Screen.clearScreen();
  Brain.Screen.drawRectangle(20, 20, 350, 100, blue);
  for(int i=0; i<100; i++){
    wait(10,msec);
    Brain.Screen.printAt(rand()*350.0/RAND_MAX, rand()*150.0/RAND_MAX," wait what ");
  }
}

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
  MotorLF.setBrake(brake);
  MotorRF.setBrake(brake);
  MotorRB.setBrake(brake);
  MotorLB.setBrake(brake);
  
  int FWSpin=0;
  // User control code here, inside the loop

  int flySpeed=0;

  while (1) {
    splitDrive();
    
    if(Controller1.ButtonL1.pressing()) spinIntk(100);
    else if(Controller1.ButtonL2.pressing())
      spinIntk(-30);
    else spinIntk(0);

    if(Controller1.ButtonX.pressing()) FWSpin=1;
    if(Controller1.ButtonR1.pressing()) FWSpin=2;
    if(Controller1.ButtonR2.pressing()) FWSpin=0;
    if(FWSpin==1){
      spinFly(flySpeed=100);
    }else if(FWSpin==2){
      spinFly(flySpeed=80);
    }else{
      MotorF1.spin(forward,0,percent);
      MotorF2.spin(forward,0,percent);
    }
    
    if(Controller1.ButtonA.pressing()) fireRing();

    if(Controller1.ButtonRight.pressing() && Controller1.ButtonY.pressing()){
      expand();
      Brain.Screen.clearScreen();
      Brain.Screen.drawRectangle(20, 20, 350, 100, blue);
      for(int i=0; i<100; i++){
        wait(10,msec);
        Brain.Screen.printAt(rand()*350.0/RAND_MAX, rand()*150.0/RAND_MAX," pneumatics fired \n                     ");
      }
    }

    wait(30, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

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
