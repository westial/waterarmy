#include "PumpMotor.h"

class FunctionalPumpMotor : public PumpMotor {
 private:
  void (*startMotor)();
  void (*stopMotor)();

 public:
  FunctionalPumpMotor(void (*startMotor)(), void (*stopMotor)()) {
    this->startMotor = startMotor;
    this->stopMotor = stopMotor;
  }

  void start() override {
    startMotor();
  }
  void stop() override {
    stopMotor();
  }
};