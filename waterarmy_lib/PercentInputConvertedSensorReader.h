#ifndef WATERARMY_MAIN_WATERARMY_LIB_PERCENTINPUTCONVERTEDSENSORREADER_H_
#define WATERARMY_MAIN_WATERARMY_LIB_PERCENTINPUTCONVERTEDSENSORREADER_H_

#include "SensorReader.h"
#include "PercentInputReader.h"

class PercentInputConvertedSensorReader : public SensorReader {

 private:
  PercentInputReader *percentReader;

 public:
  ~PercentInputConvertedSensorReader() override;

  explicit PercentInputConvertedSensorReader(PercentInputReader *percentReader);

  unsigned short percentRead() override;
};

#endif //WATERARMY_MAIN_WATERARMY_LIB_PERCENTINPUTCONVERTEDSENSORREADER_H_
