/**
 * Feature:
 * Watering use case testing scenarios.
 */
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Watering.h"
#include "waterarmy_lib_mock/MockSensorReader.cc"
#include "waterarmy_lib_mock/MockPumpMotor.cc"
#include "waterarmy_lib_mock/MockControlPanel.cc"
#include "waterarmy_lib_mock/MockPauser.cc"

using ::testing::Return;

void ExecuteWatering(unsigned short sensorReading,
                     unsigned short minMoisture,
                     unsigned short waterAmount,
                     unsigned short expectedResult,
                     unsigned long sleepMillis) {
  Watering *useCase;
  MockSensorReader sensor;
  MockControlPanel panel;
  MockPumpMotor pump;
  MockPauser pauser;

  useCase = new Watering(&sensor, &panel, &pump, &pauser);

  EXPECT_CALL(
      sensor, percentRead())
      .Times(1)
      .WillOnce(Return(sensorReading)
      );

  EXPECT_CALL(
      panel, getMinimumMoistureSetting())
      .Times(1)
      .WillOnce(Return(minMoisture)
      );

  EXPECT_CALL(
      panel, getWaterAmountSetting())
      .Times(1)
      .WillOnce(Return(waterAmount)
      );

  if (sleepMillis > 0) {
      EXPECT_CALL(
          pump, start())
          .Times(1);

      EXPECT_CALL(
          pump, stop())
          .Times(1);

      EXPECT_CALL(pauser, sleep(sleepMillis));
  }

  EXPECT_EQ(expectedResult, useCase->invoke());
}

/**
 * Scenario:
 * Watering plant when the moisture reading is lower than threshold.
 *
 * Given:
 * A Pump Motor, a Waterkeeper and a Watering use case.
 * A Sensor Reader with a previously moisture set at 19.
 * A Control Panel with moisture threshold at 20 and water amount at 10.
 *
 * When:
 * I invoke the Watering use case.
 *
 * Then:
 * Watering use case returns the irrigated water amount 10.
 */
TEST(WateringTestSuite, IrrigationBecauseMoistureUnderLimit) {
  ExecuteWatering(19, 20, 10, 10, 10000);
}

/**
 * Scenario:
 * Do not watering plant when the moisture reading is equal than threshold.
 *
 * Given:
 * A Pump Motor, a Waterkeeper and a Watering use case.
 * A Sensor Reader with a previously moisture set at 20.
 * A Control Panel with moisture threshold at 20 and water amount at 10.
 *
 * When:
 * I invoke the Watering use case.
 *
 * Then:
 * Watering use case returns the irrigated water amount 0.
 */
TEST(WateringTestSuite, NoIrrigationBecauseMoistureEqualLimit) {
  ExecuteWatering(20, 20, 10, 0, 0);
}

/**
 * Scenario:
 * Do not watering plant when the moisture reading is greater than threshold.
 *
 * Given:
 * A Pump Motor, a Waterkeeper and a Watering use case.
 * A Sensor Reader with a previously moisture set at 30.
 * A Control Panel with moisture threshold at 20 and water amount at 10.
 *
 * When:
 * I invoke the Watering use case.
 *
 * Then:
 * Watering use case returns the irrigated water amount 0.
 */
TEST(WateringTestSuite, NoIrrigationBecauseMoistureOverLimit) {
  ExecuteWatering(30, 20, 10, 0, 0);
}

TEST(WateringTestSuite, NoIrrigationBecauseMoistureOverLimit2) {
  ExecuteWatering(-3, 51, 60, 0, 0);
}