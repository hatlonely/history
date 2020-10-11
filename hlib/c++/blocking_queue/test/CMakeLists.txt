CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(BLOCKING_QUEUE)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(EXECUTABLE_OUTPUT_PATH ${BLOCKING_QUEUE_BINARY_DIR}/bin)
SET(CMAKE_CXX_FLAGS "-g -pipe -W -Wall -fPIC")
SET(WORK_ROOT "../../../../..")

AUX_SOURCE_DIRECTORY(../src SOURCES)
AUX_SOURCE_DIRECTORY(. TEST_SOURCES)
SET(SRC_LIST ${SOURCES} ${TEST_SOURCES})

INCLUDE_DIRECTORIES(
    "../include"
    "${BLOCKING_QUEUE_SOURCE_DIR}/${WORK_ROOT}/third/boost/boost-1.58.0/include"
    "${BLOCKING_QUEUE_SOURCE_DIR}/${WORK_ROOT}/google/gtest/gtest-1.6.0/include"
)

LINK_DIRECTORIES(
    "${BLOCKING_QUEUE_SOURCE_DIR}/${WORK_ROOT}/third/boost/boost-1.58.0/lib"
    "${BLOCKING_QUEUE_SOURCE_DIR}/${WORK_ROOT}/google/gtest/gtest-1.6.0/lib"
)

ADD_DEFINITIONS(
    -Dprivate=public
    -Dproctect=public
    -DGTEST_USE_OWN_TR1_TUPLE=1
)

ADD_EXECUTABLE(test_block_queue ${SRC_LIST})

TARGET_LINK_LIBRARIES(test_block_queue
    boost_system
    boost_date_time
    boost_chrono
    boost_thread
    gtest
)

ADD_CUSTOM_COMMAND(
    TARGET test_block_queue
    POST_BUILD
    COMMAND echo "${BLOCKING_QUEUE_SOURCE_DIR}"
    COMMAND echo "${BLOCKING_QUEUE_BINARY_DIR}"
)
