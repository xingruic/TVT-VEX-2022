#include "expansion.h"
#include "vex.h"

using namespace vex;

int expand_cnt=0;

void expand(){
  Pneu1.set(true);
  wait(500,msec);
  Pneu2.set(true);
}