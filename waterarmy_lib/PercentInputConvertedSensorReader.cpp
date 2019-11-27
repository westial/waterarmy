#include "PercentInputConvertedSensorReader.h"

PercentInputConvertedSensorReader::~PercentInputConvertedSensorReader() {
  delete percentReader;
}

PercentInputConvertedSensorReader::PercentInputConvertedSensorReader(
    PercentInputReader *percentReader) {
  this->percentReader = percentReader;
}

unsigned short PercentInputConvertedSensorReader::percentRead() {
  long reading = percentReader->readPercentInput();
  if (0 > reading) {
    return 0;
  } else if (100 < reading) {
    return 100;
  }
  return reading;
}
