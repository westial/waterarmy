#ifndef WATERARMY_MAIN_WATERARMY_LIB_MOCK_CONTROLPANELFUNCTIONS_H_
#define WATERARMY_MAIN_WATERARMY_LIB_MOCK_CONTROLPANELFUNCTIONS_H_

#include <gmock/gmock.h>
#include "gmock-global/gmock-global.h"

MOCK_GLOBAL_FUNC1(readMoisture, long(const long));
MOCK_GLOBAL_FUNC1(readWatering, long(const long));

#endif //WATERARMY_MAIN_WATERARMY_LIB_MOCK_CONTROLPANELFUNCTIONS_H_