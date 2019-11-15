#include "gmock/gmock.h"
#include "SensorReader.h"

class MockSensorReader : public SensorReader {
 public:
  MOCK_METHOD(unsigned short, percentRead, (), (override));
};