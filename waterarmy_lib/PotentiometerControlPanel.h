#ifndef WATERARMY_MAIN_WATERARMY_LIB_POTENTIOMETERCONTROLPANEL_H_
#define WATERARMY_MAIN_WATERARMY_LIB_POTENTIOMETERCONTROLPANEL_H_

#include "ControlPanel.h"
#include "PercentInputReader.h"

class PotentiometerControlPanel : public ControlPanel {
 private:

  PercentInputReader *moistureReader;
  PercentInputReader *wateringReader;
  long maxSeconds;

 public:

  PotentiometerControlPanel(
      PercentInputReader *moistureReader,
      PercentInputReader *wateringReader,
      long maxSeconds);

  unsigned short getMinimumMoistureSetting() override;

  unsigned long getWaterAmountSetting() override;
};

#endif //WATERARMY_MAIN_WATERARMY_LIB_POTENTIOMETERCONTROLPANEL_H_
