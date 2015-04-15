cmake_minimum_required(VERSION 2.8.4)
project(cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
OPTION (BUILD_SHARED_LIBS "Build shared libraries." ON)

# Homework 3
set(SOURCE_FILES SettingsLib/Settings.cpp SettingsLib/Util.cpp)
add_library(settings SHARED ${SOURCE_FILES})
add_executable(main SettingsLib/main.cpp)
target_link_libraries(main settings)
