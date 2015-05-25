cmake_minimum_required(VERSION 2.8.4)
project(cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
OPTION (BUILD_SHARED_LIBS "Build shared libraries." ON)

set(SOURCE_FILES ../SettingsLib/settings.cpp ../SettingsLib/Util.cpp)
add_library(settings SHARED ${SOURCE_FILES})
set(SOURCE_FILES service_manager.cpp queue.h)
add_library(servicemanager SHARED ${SOURCE_FILES})
add_executable(servicemanagerMain main.cpp writer_service.cpp)
target_link_libraries(servicemanagerMain servicemanager settings)