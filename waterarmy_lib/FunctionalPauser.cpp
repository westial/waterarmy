#include "FunctionalPauser.h"

FunctionalPauser::FunctionalPauser(void (*delay)(unsigned long)) {
  this->delay = delay;
}

void FunctionalPauser::sleep(unsigned long milliseconds) {
  delay(milliseconds);
}
