#include "expansion.h"
#include "vex.h"

using namespace vex;

int expand_cnt=0;

void expand(){
  if(expand_cnt==0){
    Pneu1.set(false);
    expand_cnt++;
  }else if(expand_cnt==1){
    Pneu2.set(false);
    expand_cnt++;
  }
}