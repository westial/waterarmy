include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
include_directories(${gmock-global_SOURCE_DIR}/include)

add_subdirectory(waterarmy_lib_mock)

add_executable(runTests watering_test.cc sensor_test.cc control_panel_test.cc)

target_link_libraries(runTests gtest gmock gtest_main)
target_link_libraries(runTests waterarmy_lib)