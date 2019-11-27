#include "FunctionalPumpMotor.h"

FunctionalPumpMotor::FunctionalPumpMotor(
    void (*startMotor)(long),
    void (*stopMotor)(long),
    const long motorId) {
  this->motorId = motorId;
  this->startMotor = startMotor;
  this->stopMotor = stopMotor;
}

void FunctionalPumpMotor::start() {
  startMotor(motorId);
}

void FunctionalPumpMotor::stop() {
  stopMotor(motorId);
}
