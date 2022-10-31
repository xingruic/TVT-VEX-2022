#include "autonomous.h"
#include "intake.h"
#include "flywheel.h"
#include "vex.h"

using namespace vex;

void _drive(int lS, int rS){
  MotorLF.spin(forward,lS,percent);
  MotorLB.spin(forward,lS,percent);
  MotorRF.spin(forward,rS,percent);
  MotorRB.spin(forward,rS,percent);
}

void driveInch(double inches){
  double pi = 3.1415926;
  int D = 4;
  MotorLF.spinFor(forward, inches/pi/D, rev, false);
  MotorLB.spinFor(forward, inches/pi/D, rev, false);
  MotorRF.spinFor(forward, inches/pi/D, rev, false);
  MotorRB.spinFor(forward, inches/pi/D, rev, true);
}

void spinInch(double inches){ // spins clockwise for how many inches
  double pi = 3.1415926;
  int D = 4;
  MotorLF.spinFor(forward, inches/pi/D, rev, false);
  MotorLB.spinFor(forward, inches/pi/D, rev, false);
  MotorRF.spinFor(reverse, inches/pi/D, rev, false);
  MotorRB.spinFor(reverse, inches/pi/D, rev, true);
}

void auton::Half1Discs(){
  driveInch(-60);
  spinInch(-1.6);
  spinFly(90);
  wait(2300,msec);
  int oldFly=0;
  while(MotorF2.velocity(percent)>90*0.8 && MotorF2.velocity(percent)>oldFly){
    oldFly=MotorF2.velocity(percent);
  }
  fireRing();
  spinFly(90);
  wait(1000,msec);
  while(MotorF2.velocity(percent)>90*0.8 && MotorF2.velocity(percent)>oldFly){
    oldFly=MotorF2.velocity(percent);
  }
  fireRing();
  fireRing();
  wait(300,msec);
  spinFly(0);
}

void auton::Half1(){
  // roller
  _drive(20,20);
  wait(200, msec);
  _drive(5, 5);
  spinIntk(40);
  wait(700, msec);
  spinIntk(0);
  _drive(0,0);

  // NOTE: please do NOT add additional code here, I re-used this code for Half2()
  // if you want the discs code, call Half1Discs() after this
}

void auton::Half2(){
  // roller
  driveInch(-36);
  spinInch(-15);
  _drive(70,70);
  wait(300,msec);
  _drive(0,0);
  wait(100,msec);
  
  Half1();
  

  // discs
  driveInch(-70);
  spinInch(3.6);

  spinFly(90);
  wait(2300,msec);
  int oldFly;
  while(MotorF2.velocity(percent)>90*0.8 && MotorF2.velocity(percent)>oldFly){
    oldFly=MotorF2.velocity(percent);
  };
  fireRing();
  spinFly(90);
  wait(1000,msec);
  while(MotorF2.velocity(percent)>90*0.8 && MotorF2.velocity(percent)>oldFly){
    oldFly=MotorF2.velocity(percent);
  };
  fireRing();
  fireRing();
  wait(300,msec);
  spinFly(0);

  // reset (for debugging)
  spinInch(-3);
  driveInch(50);
}