#include "SensorReader.h"
#include "PercentInputReader.h"

class PercentInputConvertedSensorReader : public SensorReader {

 private:
  PercentInputReader *percentReader;

 public:
  ~PercentInputConvertedSensorReader() override {
    delete percentReader;
  }

  explicit PercentInputConvertedSensorReader(PercentInputReader *percentReader) {
    this->percentReader = percentReader;
  }

  unsigned short percentRead() override {
    return percentReader->readPercentInput();
  }
};