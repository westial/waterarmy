//
// Created by jaume on 11/11/19.
//

#ifndef WATERARMY_MAIN_WATERARMY_LIB_PAUSER_H_
#define WATERARMY_MAIN_WATERARMY_LIB_PAUSER_H_

class Pauser {
 public:
  virtual ~Pauser() = default;
  virtual void sleep(unsigned long milliseconds) = 0;
};

#endif //WATERARMY_MAIN_WATERARMY_LIB_PAUSER_H_
