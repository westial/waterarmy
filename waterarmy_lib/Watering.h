//
// Created by jaume on 11/7/19.
//

#ifndef WATERARMY_MAIN_WATERARMY_LIB_WATERING_H_
#define WATERARMY_MAIN_WATERARMY_LIB_WATERING_H_

#include "SensorReader.h"
#include "PumpMotor.h"
#include "ControlPanel.h"
#include "Pauser.h"
/**
 * @brief Watering use case.
 *
 * This use case handles a plant irrigation and returns the number of seconds
 * last by.
 */
class Watering {

 private:
  SensorReader *sensor;
  PumpMotor *pump;
  ControlPanel *panel;
  Pauser *pauser;

 public:
  Watering(
      SensorReader *sensor,
      ControlPanel *panel,
      PumpMotor *pump,
      Pauser *pauser
      );
  ~Watering();
  unsigned short invoke();

};

#endif //WATERARMY_MAIN_WATERARMY_LIB_WATERING_H_
