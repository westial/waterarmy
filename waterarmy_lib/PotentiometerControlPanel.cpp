#include "PotentiometerControlPanel.h"

PotentiometerControlPanel::PotentiometerControlPanel(
    PercentInputReader *moistureReader,
    PercentInputReader *wateringReader,
    const long maxSeconds) {
  this->moistureReader = moistureReader;
  this->wateringReader = wateringReader;
  this->maxSeconds = maxSeconds;
}

unsigned short PotentiometerControlPanel::getMinimumMoistureSetting() {
  return moistureReader->readPercentInput();
}

unsigned long PotentiometerControlPanel::getWaterAmountSetting() {
  double wateringSeconds = ((double) maxSeconds) * ((double) wateringReader->readPercentInput() / 100.0);
  return (long) wateringSeconds;
}
