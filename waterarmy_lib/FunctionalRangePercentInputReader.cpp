#include "FunctionalRangePercentInputReader.h"
FunctionalRangePercentInputReader::FunctionalRangePercentInputReader(
    Percentage *percentage,
    long (*readInputFunc)(const long),
    long minimum,
    long maximum,
    long readerId) {
  this->percentage = percentage;
  this->readInputFunc = readInputFunc;
  this->minimum = minimum;
  this->maximum = maximum;
  this->readerId = readerId;

}

long FunctionalRangePercentInputReader::readPercentInput() {
  long reading = readInputFunc(readerId);
  return percentage->calculate(minimum, maximum, reading);
}
