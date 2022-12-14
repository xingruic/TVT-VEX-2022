#include "autonomous.h"
#include "intake.h"
#include "flywheel.h"
#include "vex.h"

// #define DO_DISKS_IN_AUTON

using namespace vex;

void _spinFly(int speed){
  MotorF1.spin(forward,speed,percent);
  MotorF2.spin(forward,speed,percent);
}

void setVel(int vel){
  MotorLF.setVelocity(vel, percent);
  MotorLB.setVelocity(vel, percent);
  MotorRF.setVelocity(vel, percent);
  MotorRB.setVelocity(vel, percent);
}

void _drive(int lS, int rS){
  MotorLF.spin(forward,lS,percent);
  MotorLB.spin(forward,lS,percent);
  MotorRF.spin(forward,rS,percent);
  MotorRB.spin(forward,rS,percent);
}

void driveInch(double inches){
  double x=0;
  int speed;
  const double kp=7;
  const double margin=0.3;
  double error=inches-x;
  MotorRB.setRotation(0, rev);
  while(fabs(error)>margin){
    if(kp*error>50){
      speed=50;
    }else if(kp*error<-50){
      speed=-50;
    }else{
      speed=kp*error;
    }
    _drive(speed,speed);
    x=MotorRB.position(rev)*3.14159*4;
    error=inches-x;
  }
  _drive(0,0);
}

void spinInch(double inches){ // spins clockwise for how many inches
  setVel(30);
  MotorLF.spinFor(forward, inches/3.14159/4, rev, false);
  MotorLB.spinFor(forward, inches/3.14159/4, rev, false);
  MotorRF.spinFor(reverse, inches/3.14159/4, rev, false);
  MotorRB.spinFor(reverse, inches/3.14159/4, rev, true);
}

void auton::Half1Discs(){
#ifdef DO_DISKS_IN_AUTON
  driveInch(-7);
  spinInch(5.2);
  driveInch(-40);
  spinInch(-8);
  // driveInch(-7);
  spinFlyForMsec(90,4000);
  fireRing();
  spinFlyForMsec(96,3000);
  fireRing();
  spinFlyForMsec(96,500);
  fireRing();
  spinFlyForMsec(96,500);
  fireRing();
  wait(500,msec);
  _spinFly(0);
#endif
}

void auton::Half1(){
  // roller
  _drive(20,20);
  wait(200, msec);
  _drive(5, 5);
  spinIntk(-40);
  wait(300, msec);
  spinIntk(0);
  _drive(0,0);

  // NOTE: please do NOT add additional code here, I re-used this code for Half2()
  // if you want the discs code, call Half1Discs() after this
}

void auton::Half2(){
  // roller
  driveInch(-24);
  spinInch(-10);
  _drive(60,60);
  wait(200,msec);
  _drive(5, 5);
  spinIntk(-70);
  wait(170,msec);
  _drive(0,0);
  wait(100,msec);
  spinIntk(0);

  // discs
#ifdef DO_DISKS_IN_AUTON
  driveInch(-5);
  spinInch(-6);
  driveInch(-40);
  spinInch(10);
  driveInch(-7);
  spinFlyForMsec(90,4000);
  fireRing();
  spinFlyForMsec(96,3000);
  fireRing();
  spinFlyForMsec(96,500);
  fireRing();
  spinFlyForMsec(96,500);
  fireRing();
  wait(500,msec);
  _spinFly(0);
#endif
  // // reset (for debugging)
  // spinInch(-3);
  // driveInch(50);
}

void auton::ProgSklz(){
  // two rollers + 1 disk
  _drive(20,20);
  wait(200, msec);
  _drive(5, 5);
  spinIntk(40);
  wait(800, msec);
  spinIntk(0);
  _drive(0,0);

  driveInch(-10);
  spinInch(13);
  spinIntk(90);
  driveInch(30);
  driveInch(-10);
  spinInch(-13);
  driveInch(-23);
  spinInch(13);
  spinIntk(0);
  driveInch(6);
  _drive(20,20);
  wait(200, msec);
  _drive(5, 5);
  spinIntk(40);
  wait(1400, msec);
  spinIntk(0);
  _drive(0,0);


  // drive and shoot
  driveInch(-9);
  spinInch(-13);
  driveInch(-30);
  spinInch(-1);
  _spinFly(90);
  wait(2300,msec);
  int oldFly=0;
  while(MotorF2.velocity(percent)>83*0.8 && MotorF2.velocity(percent)>oldFly){
    oldFly=MotorF2.velocity(percent);
  }
  fireRing();
  wait(500,msec);
  while(MotorF2.velocity(percent)>80*0.8 && MotorF2.velocity(percent)>oldFly){
    oldFly=MotorF2.velocity(percent);
  }
  fireRing();
  wait(500,msec);
  while(MotorF2.velocity(percent)>80*0.8 && MotorF2.velocity(percent)>oldFly){
    oldFly=MotorF2.velocity(percent);
  }
  fireRing();
  wait(500,msec);
  fireRing();
  wait(500,msec);
  fireRing();
  _spinFly(0);

  driveInch(42);
  spinInch(6);

  // Uncomment this if you have to wait until last 10 seconds to launch in skillz contest
  // while(Brain.Timer.time(seconds)<55) wait(1,sec);

  Pneu2.set(false);
  wait(500,msec);
  Pneu1.set(false);
}