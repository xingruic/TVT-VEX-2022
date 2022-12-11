#include "expansion.h"
#include "vex.h"

using namespace vex;

int expand_cnt=0;

void expand(){
  Pneu2.set(false);
  wait(500,msec);
  Pneu1.set(false);
}