#include "flywheel.h"
#include "vex.h"

using namespace vex;

int F1speed=0;
int f1prev_error=-1;
int f1tbh=0;
const float f1gain=0.3;

void spinF1(int speed){
  int error=speed-F1speed;
  int output=(F1speed=MotorF1.velocity(percent))+error*f1gain;
  if(signbit(error)!=signbit(f1prev_error)){
    output=0.5*(output+f1tbh);
    f1tbh=output;
    f1prev_error=error;
  }
  MotorF1.spin(forward,output,percent);
}

int F2speed=0;
int f2prev_error=-1;
int f2tbh=0;
const float f2gain=0.3;

void spinF2(int speed){
  int error=speed-F2speed;
  int output=(F2speed=MotorF2.velocity(percent))+error*f2gain;
  if(signbit(error)!=signbit(f2prev_error)){
    output=0.5*(output+f2tbh);
    f2tbh=output;
    f2prev_error=error;
  }
  MotorF2.spin(forward,output,percent);
}

void spinFly(int speed){
  spinF1(speed);
  spinF2(speed*0.9);
  // if(speed>0 && MotorF2.velocity(percent)>speed*0.8 && MotorF2.velocity(percent)>oldFly){
  //   Controller1.rumble(".");
  // }else{
  //   Controller1.rumble(" ");
  // }
  // oldFly=MotorF2.velocity(percent);
  Brain.Screen.printAt(30,30,"flywheel speed: %.2f                  ", MotorF2.velocity(percent));
}

void spinFlyForMsec(int speed, int msecs, bool stopAfterwards){
  for(int i=0; i<msecs/20; i++){
    spinFly(speed);
    wait(20,msec);
  }
  if(stopAfterwards){
    MotorF1.spin(forward,0,percent);
    MotorF2.spin(forward,0,percent);
  }
}

// fire ring
void fireRing(){
  MotorOut.spin(forward, 100, percent);
  wait(100, msec);
  MotorOut.spin(reverse, 100, percent);
  wait(220, msec);
  MotorOut.spin(forward, 0, percent);
}

void tripleFire(int flySpeed=0){
  fireRing();
  wait(30,msec);
  fireRing();
  wait(30,msec);
  fireRing();
  wait(30,msec);
}