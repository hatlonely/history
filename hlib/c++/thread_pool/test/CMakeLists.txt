CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(THREAD_POOL)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(EXECUTABLE_OUTPUT_PATH ${THREAD_POOL_BINARY_DIR}/bin)
SET(CMAKE_CXX_FLAGS "-g -pipe -W -Wall -fPIC")
SET(WORK_ROOT "../../../../..")

AUX_SOURCE_DIRECTORY(../src SOURCES)
AUX_SOURCE_DIRECTORY(. TEST_SOURCES)
SET(SRC_LIST ${SOURCES} ${TEST_SOURCES})

INCLUDE_DIRECTORIES(
    "../include"
    "../../blocking_queue/include/"
    "${THREAD_POOL_SOURCE_DIR}/${WORK_ROOT}/third/boost/boost-1.58.0/include"
    "${THREAD_POOL_SOURCE_DIR}/${WORK_ROOT}/google/gtest/gtest-1.6.0/include"
)

LINK_DIRECTORIES(
    "${THREAD_POOL_SOURCE_DIR}/${WORK_ROOT}/third/boost/boost-1.58.0/lib"
    "${THREAD_POOL_SOURCE_DIR}/${WORK_ROOT}/google/gtest/gtest-1.6.0/lib"
)

ADD_DEFINITIONS(
    -Dprivate=public
    -Dproctect=public
    -DGTEST_USE_OWN_TR1_TUPLE=1
)

ADD_EXECUTABLE(test_thread_pool ${SRC_LIST})

TARGET_LINK_LIBRARIES(test_thread_pool
    boost_system
    boost_date_time
    boost_chrono
    boost_thread
    gtest
)

ADD_CUSTOM_COMMAND(
    TARGET test_thread_pool
    POST_BUILD
    COMMAND echo "${THREAD_POOL_SOURCE_DIR}"
    COMMAND echo "${THREAD_POOL_BINARY_DIR}"
)
