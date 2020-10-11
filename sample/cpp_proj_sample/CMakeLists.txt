CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(CPP_PROJ_SAMPLE)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(VERSION "v0.0.0")
SET(WORK_ROOT "../")
IF(debug)
    SET(CMAKE_CXX_FLAGS "-std=c++11 -g")
ELSE()
    SET(CMAKE_CXX_FLAGS "-std=c++11 -O2")
    ADD_DEFINITIONS(-DNO_DEBUG=1)
ENDIF()
IF(gprof)
    SET(CMAKE_CXX_FLAGS "-std=c++11 -pg -g")
    ADD_DEFINITIONS(-DGPROF=1)
ENDIF()
IF(gcov)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC")
ENDIF()

AUX_SOURCE_DIRECTORY(src/server SERVER)
AUX_SOURCE_DIRECTORY(src/client CLIENT)
AUX_SOURCE_DIRECTORY(proto_out PROTO)

INCLUDE_DIRECTORIES(
    "include/"
    "src/common/"
    "proto_out/"
    "/usr/local/include/"
)

LINK_DIRECTORIES(
    "/usr/local/lib/"
)

ADD_DEFINITIONS(
    -DCPP_PROJ_SAMPLE_VERSION="${VERSION}"
)

ADD_EXECUTABLE(greeter_server ${SERVER} ${PROTO})
ADD_EXECUTABLE(greeter_client ${CLIENT} ${PROTO})

TARGET_LINK_LIBRARIES(
    greeter_server
    protobuf
    grpc
    grpc++
    config++
    log4cplus
)

TARGET_LINK_LIBRARIES(
    greeter_client
    protobuf
    grpc
    grpc++
    log4cplus
)

ADD_CUSTOM_COMMAND(
    TARGET greeter_server
    POST_BUILD
    COMMAND rm -rf ${CPP_PROJ_SAMPLE_BINARY_DIR}/output/
    COMMAND mkdir -p ${CPP_PROJ_SAMPLE_BINARY_DIR}/output/bin/
    COMMAND mkdir -p ${CPP_PROJ_SAMPLE_BINARY_DIR}/output/conf/
    COMMAND mkdir -p ${CPP_PROJ_SAMPLE_BINARY_DIR}/output/log/
    COMMAND cp -rf ${CPP_PROJ_SAMPLE_BINARY_DIR}/greeter_server ${CPP_PROJ_SAMPLE_BINARY_DIR}/output/bin/
    COMMAND cp -rf ${CPP_PROJ_SAMPLE_BINARY_DIR}/greeter_client ${CPP_PROJ_SAMPLE_BINARY_DIR}/output/bin/
    COMMAND cp -rf ${CPP_PROJ_SAMPLE_SOURCE_DIR}/conf/*.cfg ${CPP_PROJ_SAMPLE_BINARY_DIR}/output/conf/
    COMMAND cp -rf ${CPP_PROJ_SAMPLE_SOURCE_DIR}/conf/*.ini ${CPP_PROJ_SAMPLE_BINARY_DIR}/output/conf/
)

