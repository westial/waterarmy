#ifndef WATERARMY_MAIN_WATERARMY_LIB_FUNCTIONALRANGEPERCENTINPUTREADER_H_
#define WATERARMY_MAIN_WATERARMY_LIB_FUNCTIONALRANGEPERCENTINPUTREADER_H_

#include "PercentInputReader.h"
#include "Percentage.h"


class FunctionalRangePercentInputReader : public PercentInputReader {
 private:
  Percentage *percentage;
  long (*readInputFunc)(const long);
  long lowest;
  long highest;
  long readerId;

 public:
  FunctionalRangePercentInputReader(
      Percentage *percentage,
      long (*readInputFunc)(const long),
      long lowest,
      long highest,
      long readerId) {
    this->percentage = percentage;
    this->readInputFunc = readInputFunc;
    this->lowest = lowest;
    this->highest = highest;
    this->readerId = readerId;
  }

  long readPercentInput() override {
    long reading = readInputFunc(readerId);
    return percentage->calculate(lowest, highest, reading);
  }
};

#endif // WATERARMY_MAIN_WATERARMY_LIB_FUNCTIONALRANGEPERCENTINPUTREADER_H_