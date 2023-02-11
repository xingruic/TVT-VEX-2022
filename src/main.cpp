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
// Vision               vision        8               
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// Vision               vision        4               
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// Vision               vision        4               
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// Vision               vision        4               
// ---- END VEXCODE CONFIGURED DEVICES ----
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
#include<string>

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

bool redAlliance=0;

void screenInit(){
  Brain.Screen.drawRectangle(0, 0, 240, 272, yellow);
  Brain.Screen.printAt(20,50,"Half1()");
  Brain.Screen.drawRectangle(0, 240, 200, 270, blue);
  Brain.Screen.printAt(260,50,"Half2()");
}

void extraordinaryPrint(std::string str){
  Brain.Screen.clearScreen();
  Brain.Screen.drawRectangle(20, 20, 350, 100, blue);
  for(int i=0; i<100; i++){
    wait(10,msec);
    Brain.Screen.printAt(rand()*350.0/RAND_MAX, rand()*150.0/RAND_MAX,str.c_str());
  }
}

// give lSpeed and rSpeed in percent
void drive(int lS, int rS){
  MotorLF.spin(forward,lS,percent);
  MotorLB.spin(forward,lS,percent);
  MotorRF.spin(forward,rS,percent);
  MotorRB.spin(forward,rS,percent);
}

bool pneu_rev=1;

enum auton_mode{
  half2,
  half1,
  progsklz
}autonMode=half2;

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

  Gyro.calibrate();
  while(Gyro.isCalibrating()) wait(20,msec);
  screenInit();
  Brain.Screen.pressed(switchAlliance);
}

void autonomous(void) {
  MotorLF.setBrake(brake);
  MotorLB.setBrake(brake);
  MotorRF.setBrake(brake);
  MotorRB.setBrake(brake);
  // while(1){
  //   wait(20,msec);
  //   Vision.takeSnapshot(redAlliance?Vision__RED_:Vision__BLUE_);
  //   Brain.Screen.printAt(30, 30, "X Val: %d          \n\nY Val: %d         ", Vision.largestObject.centerX, Vision.largestObject.centerY);
  // }
  Brain.resetTimer();
  switch(autonMode){
    case half2:
  auton::Half2();
    break;
    case half1:
  auton::Half1();
    break;
    case progsklz:
  auton::ProgSklz();
    break;
    default:
    break;
  }
  extraordinaryPrint("wait what");
}

void singleRightDrive(){
  int LR = Controller1.Axis1.position();
  int FB = Controller1.Axis2.position();
  double lD = LR*0.9;
  double rD = -LR*0.9;
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
  double lD = LR*0.9;
  double rD = -LR*0.9;
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
  double lD = LR;
  double rD = -LR;
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

  MotorF1.setBrake(coast);
  MotorF2.setBrake(coast);
  
  int FWSpin=0;
  // User control code here, inside the loop

  task flyTask=task(flyControl);

  while (1) {
    splitDrive();
    
    if(Controller1.ButtonL1.pressing()) spinIntk(100);
    else if(Controller1.ButtonL2.pressing())
      spinIntk(-100);
    else spinIntk(0);

    if(Controller1.ButtonB.pressing()) FWSpin=3;
    if(Controller1.ButtonR1.pressing()) FWSpin=2;
    if(Controller1.ButtonX.pressing()) FWSpin=1;
    if(Controller1.ButtonR2.pressing()) FWSpin=0;
    if(FWSpin==3){
      setFlyTarget(75);
    }else if(FWSpin==2){
      setFlyTarget(85);
    }else if(FWSpin==1){
      setFlyTarget(100);
    }else{
      setFlyTarget(0);
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

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
