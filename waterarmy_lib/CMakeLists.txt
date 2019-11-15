project(waterarmy_lib)

set(HEADER_FILES
        Watering.h
        PumpMotor.h
        SensorReader.h
        ControlPanel.h
        Pauser.h
        wateringfunctions.h Percentage.cpp Percentage.h PercentInputReader.h)

set(SOURCE_FILES
        Watering.cpp
        PercentInputConvertedSensorReader.cpp Percentage.cpp Percentage.h PotentiometerControlPanel.cpp PercentInputReader.h FunctionalRangePercentInputReader.cpp FunctionalPumpMotor.cpp FunctionalPauser.cpp)

add_library(waterarmy_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})