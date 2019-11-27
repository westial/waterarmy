#ifndef WATERARMY_MAIN_WATERARMY_LIB_FUNCTIONALRANGEPERCENTINPUTREADER_H_
#define WATERARMY_MAIN_WATERARMY_LIB_FUNCTIONALRANGEPERCENTINPUTREADER_H_

#include "PercentInputReader.h"
#include "Percentage.h"

class FunctionalRangePercentInputReader : public PercentInputReader {
 private:
  Percentage *percentage;
  long (*readInputFunc)(const long);
  long minimum;
  long maximum;
  long readerId;

 public:
  FunctionalRangePercentInputReader(
      Percentage *percentage,
      long (*readInputFunc)(const long),
      long minimum,
      long maximum,
      long readerId);

  long readPercentInput() override;
};

#endif // WATERARMY_MAIN_WATERARMY_LIB_FUNCTIONALRANGEPERCENTINPUTREADER_H_