#ifndef WATERARMY_MAIN_WATERARMY_LIB_FUNCTIONALPAUSER_H_
#define WATERARMY_MAIN_WATERARMY_LIB_FUNCTIONALPAUSER_H_

#include "Pauser.h"

class FunctionalPauser : public Pauser {
 private:

  void (*delay)(unsigned long);

 public:

  explicit FunctionalPauser(void (*delay)(unsigned long));

  void sleep(unsigned long milliseconds) override;

};

#endif //WATERARMY_MAIN_WATERARMY_LIB_FUNCTIONALPAUSER_H_
