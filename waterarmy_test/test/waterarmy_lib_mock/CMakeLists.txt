project(waterarmy_lib_mock)

set(SOURCE_FILES
        MockSensorReader.cc
        MockPumpMotor.cc
        MockControlPanel.cc
        MockPauser.cc
        mocksensorfunctions.cc
        mockcontrolpanelfunctions.cc)

add_library(waterarmy_lib_mock STATIC ${SOURCE_FILES} ${HEADER_FILES})