cmake_minimum_required(VERSION 2.8.4)
project(hw1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES    main.cpp
                    parser.cpp)

add_executable(hw1 ${SOURCE_FILES})
