//
// Created by jaume on 11/8/19.
//

#ifndef WATERARMY_MAIN_WATERARMY_LIB_PUMPMOTOR_H_
#define WATERARMY_MAIN_WATERARMY_LIB_PUMPMOTOR_H_

class PumpMotor {
 public:
  virtual ~PumpMotor() = default;
  virtual void start() = 0;
  virtual void stop() = 0;
};

#endif //WATERARMY_MAIN_WATERARMY_LIB_PUMPMOTOR_H_
