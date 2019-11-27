#include "Watering.h"
#include "ControlPanel.h"

unsigned short Watering::invoke() {
  unsigned short reading = sensor->percentRead();
  unsigned short wateringSeconds = panel->getWaterAmountSetting();
  const unsigned short NO_WATERING = 0;
  if (panel->getMinimumMoistureSetting() > reading) {
    pump->start();
    pauser->sleep(wateringSeconds * 1000);
    pump->stop();
    return wateringSeconds;
  }
  return NO_WATERING;
}

Watering::Watering(
    SensorReader *sensor,
    ControlPanel *panel,
    PumpMotor *pump,
    Pauser *pauser
) {
  this->sensor = sensor;
  this->pump = pump;
  this->panel = panel;
  this->pauser = pauser;
}

Watering::~Watering() = default;
