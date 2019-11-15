/**
 * Feature:
 * Sensor units testing
 *
 * Given:
 * A mocked function for reading that returns value as MOCK_READING
 * A Functional Range Percent Input Reader with the lowest value as LOWEST and highest value as HIGHEST
 * A Functional Sensor Reader entity
 *
 * When:
 * I call sensor for the percent read.
 *
 * Then:
 * Sensor returns EXPECTED.
 */
#include <SensorReader.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "gmock-global/gmock-global.h"
#include "PercentInputConvertedSensorReader.cpp"
#include "FunctionalRangePercentInputReader.cpp"
#include "waterarmy_lib_mock/mocksensorfunctions.cc"

using ::testing::Return;

void ExecutePercentTest(const unsigned short sensorId,
                        const long lowest,
                        const long highest,
                        const long mockReading,
                        const long expected) {
  PercentInputReader *inputReader = new FunctionalRangePercentInputReader(
      new Percentage(),
      readSensor,
      lowest,
      highest,
      sensorId
      );

  SensorReader *sensor = new PercentInputConvertedSensorReader(inputReader);

  EXPECT_GLOBAL_CALL(
      readSensor,
      readSensor(sensorId))
      .Times(1)
      .WillOnce(Return(mockReading));

  EXPECT_EQ(expected, sensor->percentRead());
}

/**
 * Scenario:
 * Calculate the percent for the given very basic range and value.
 */
TEST(SensorTestSuite, BasicValues) {
  ExecutePercentTest(12, 0, 100, 30, 30);
}

/**
 * Scenario:
 * Calculate the percent for the given negative range and negative value.
 */
TEST(SensorTestSuite, NegativeValues) {
  ExecutePercentTest(12, -910, -10, -460, 50);
}

/**
 * Scenario:
 * Calculate the percent for the given positive/negative mixed ranges and values.
 */
TEST(SensorTestSuite, MixedValues) {
  ExecutePercentTest(9, -99, 901, 501, 60);
  ExecutePercentTest(10, -10000, 30005, 12345, 55);
}

/**
 * Scenario:
 * Calculate the percent for the given lower highest than lowest value.
 */
TEST(SensorTestSuite, InvertedRange) {
  ExecutePercentTest(13, 100, 0, 50, 50);
}
