#include "Pauser.h"

class FunctionalPauser : public Pauser {
 private:
  void (*delay)(unsigned long);
 public:
  explicit FunctionalPauser(void (*delay)(unsigned long)) {
    this->delay = delay;
  }
  void sleep(unsigned long milliseconds) override {
    delay(milliseconds);
  }
};