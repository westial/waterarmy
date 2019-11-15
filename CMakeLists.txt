cmake_minimum_required(VERSION 3.13)
project(waterarmy_main)

set(CMAKE_CXX_STANDARD 17)

include_directories(waterarmy_lib)

add_executable(waterarmy_main_run main.cpp)

add_subdirectory(waterarmy_lib)
add_subdirectory(waterarmy_test)

target_link_libraries(waterarmy_main_run waterarmy_lib)