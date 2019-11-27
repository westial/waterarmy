#ifndef WATERARMY_MAIN_WATERARMY_LIB_FUNCTIONALPUMPMOTOR_H_
#define WATERARMY_MAIN_WATERARMY_LIB_FUNCTIONALPUMPMOTOR_H_

#include "PumpMotor.h"

class FunctionalPumpMotor : public PumpMotor {
 private:

  void (*startMotor)(long);
  void (*stopMotor)(long);
  long motorId;

 public:

  FunctionalPumpMotor(
      void (*startMotor)(long),
      void (*stopMotor)(long),
      long motorId);

  void start() override;

  void stop() override;
};

#endif //WATERARMY_MAIN_WATERARMY_LIB_FUNCTIONALPUMPMOTOR_H_
