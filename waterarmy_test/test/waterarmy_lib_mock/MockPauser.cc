#include <Pauser.h>
#include "gmock/gmock.h"

class MockPauser : public Pauser {
 public:
  MOCK_METHOD(void, sleep, (unsigned long), (override));
};