CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(TEST_HELLO_WORDS)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_CXX_FLAGS "-std=c++11")
SET(WORK_ROOT "../../../..")

SET(SRC_LIST ../src/hellowords.cpp ./test_hellowords.cpp)

INCLUDE_DIRECTORIES(
    "../include"
    "/usr/local/include/"
    "${TEST_HELLO_WORDS_SOURCE_DIR}/${WORK_ROOT}/google/gtest/gtest-1.6.0/include"
)

LINK_DIRECTORIES(
    "/usr/local/lib/"
    "${TEST_HELLO_WORDS_SOURCE_DIR}/${WORK_ROOT}/google/gtest/gtest-1.6.0/lib"
)

ADD_DEFINITIONS(
    # add this marco for mac
    -DGTEST_USE_OWN_TR1_TUPLE=1
    -Dprivate=public
    -Dprotected=public
)


ADD_EXECUTABLE(test_hellowords ${SRC_LIST})

TARGET_LINK_LIBRARIES(
    test_hellowords
    gtest
)
