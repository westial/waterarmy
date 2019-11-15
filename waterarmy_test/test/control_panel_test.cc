/**
 * Feature:
 * Control Panel units testing
 *
 * Given:
 * A mocked function for reading the moisture setting that returns value as MOCK_MOISTURE_READING
 * A Functional Range Percent Input Reader for moisture setting with the lowest value as MOISTURE_LOWEST and highest value as MOISTURE_HIGHEST
 * A mocked function for reading the watering seconds setting that returns value as MOCK_WATERING_READING
 * A Functional Range Percent Input Reader for watering seconds setting with the lowest value as WATERING_LOWEST and highest value as WATERING_HIGHEST
 * A Potentiometer Control Panel entity
 *
 * When:
 * I call control panel for the moisture and watering settings.
 *
 * Then:
 * Control Panel returns MOISTURE_EXPECTED and WATERING_EXPECTED respectively.
 */

#include <ControlPanel.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "gmock-global/gmock-global.h"
#include "PotentiometerControlPanel.cpp"
#include "FunctionalRangePercentInputReader.cpp"
#include "waterarmy_lib_mock/mockcontrolpanelfunctions.cc"

using ::testing::Return;

/**
 * Scenario:
 * Get the moisture and watering setting with standard values.
 */
TEST(ControlPanelTestSuite, BasicValues) {
  PercentInputReader *moisturePot = new FunctionalRangePercentInputReader(
      new Percentage(),
      readMoisture,
      0,
      500,
      1
  );

  PercentInputReader *wateringPot = new FunctionalRangePercentInputReader(
      new Percentage(),
      readWatering,
      500,
      1000,
      2
  );

  ControlPanel *controlPanel = new PotentiometerControlPanel(
      moisturePot,
      wateringPot
  );

  EXPECT_GLOBAL_CALL(
      readMoisture,
      readMoisture(1))
      .Times(1)
      .WillOnce(Return(250));

  EXPECT_EQ(50, controlPanel->getMinimumMoistureSetting());

  EXPECT_GLOBAL_CALL(
      readWatering,
      readWatering(2))
      .Times(1)
      .WillOnce(Return(900));

  EXPECT_EQ(80, controlPanel->getWaterAmountSetting());
}