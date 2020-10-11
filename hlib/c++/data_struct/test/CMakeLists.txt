CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(DATA_STRUCT)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_CXX_FLAGS "-g -pipe -fPIC -std=c++11")
SET(WORK_ROOT "../../../../../")

SET(TEST_LINKED_LIST test_linked_list.cpp)

INCLUDE_DIRECTORIES(
    "../include"
    "${DATA_STRUCT_SOURCE_DIR}/${WORK_ROOT}/google/gtest/gtest-1.6.0/include"
)

LINK_DIRECTORIES(
    "${DATA_STRUCT_SOURCE_DIR}/${WORK_ROOT}/google/gtest/gtest-1.6.0/lib"
)

ADD_DEFINITIONS(
    # add this marco for mac
    -DGTEST_USE_OWN_TR1_TUPLE=1
)

ADD_EXECUTABLE(test_linked_list ${TEST_LINKED_LIST})

TARGET_LINK_LIBRARIES(test_linked_list
    gtest
)

