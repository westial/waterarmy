#include <PumpMotor.h>
#include "gmock/gmock.h"

class MockPumpMotor : public PumpMotor {
 public:
  MOCK_METHOD(void, start, (), (override));
  MOCK_METHOD(void, stop, (), (override));
};
