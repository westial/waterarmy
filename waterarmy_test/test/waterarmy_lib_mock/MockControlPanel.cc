#include <ControlPanel.h>
#include "gmock/gmock.h"

class MockControlPanel : public ControlPanel {
 public:
    MOCK_METHOD(unsigned short, getMinimumMoistureSetting, (), (override));
    MOCK_METHOD(unsigned short, getWaterAmountSetting, (), (override));
};