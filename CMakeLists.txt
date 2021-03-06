cmake_minimum_required(VERSION 2.8.4)
project(cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
OPTION (BUILD_SHARED_LIBS "Build shared libraries." ON)

# Homework 3
set(SOURCE_FILES SettingsLib/settings.cpp SettingsLib/Util.cpp)
add_library(settings SHARED ${SOURCE_FILES})
add_executable(settingsMain SettingsLib/main.cpp ServiceManager/service_manager.cpp ServiceManager/service_manager.h)
target_link_libraries(settingsMain settings)

# Homework 4
set(SOURCE_FILES ServiceManager/service_manager.cpp ServiceManager/queue.h)
add_library(servicemanager SHARED ${SOURCE_FILES})
add_executable(servicemanagerMain ServiceManager/main.cpp ServiceManager/writer_service.cpp)
target_link_libraries(servicemanagerMain servicemanager settings)


# Unit Tests
set(SOURCE_FILES Tester/tester.cpp)
add_executable(tester ${SOURCE_FILES})
target_link_libraries(tester settings)