#include "ControlPanel.h"
#include "PercentInputReader.h"

class PotentiometerControlPanel : public ControlPanel {
 private:
  PercentInputReader *moistureReader;
  PercentInputReader *wateringReader;

 public:
  PotentiometerControlPanel(
      PercentInputReader *moistureReader,
      PercentInputReader *wateringReader) {
    this->moistureReader = moistureReader;
    this->wateringReader = wateringReader;
  }

  unsigned short getMinimumMoistureSetting() override {
    return moistureReader->readPercentInput();
  }

  unsigned short getWaterAmountSetting() override {
    return wateringReader->readPercentInput();
  };
};