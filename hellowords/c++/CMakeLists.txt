CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(HELLO_WORDS)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_CXX_FLAGS "-std=c++11")
SET(WORK_ROOT "../../../..")

SET(SRC_LIST src/hellowords.cpp src/main.cpp)

INCLUDE_DIRECTORIES(
    "./include"
    "/usr/local/include/"
)

LINK_DIRECTORIES(
    "/usr/local/lib/"
)

ADD_DEFINITIONS(
)

ADD_EXECUTABLE(hellowords ${SRC_LIST})

TARGET_LINK_LIBRARIES(
    hellowords
    event
    event_core
)
