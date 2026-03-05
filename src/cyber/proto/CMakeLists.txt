cmake_minimum_required(VERSION 3.16)

project(cyber_proto)

set(CMAKE_CXX_STANDARD 14)

# protobuf
set(PROTOBUF_ROOT ${CMAKE_SOURCE_DIR}/thirdparty)

set(PROTOC_EXECUTABLE ${PROTOBUF_ROOT}/protoc)
set(PROTOBUF_INCLUDE_DIR ${PROTOBUF_ROOT}/include)
set(PROTOBUF_LIB_DIR ${PROTOBUF_ROOT}/lib)
set(PROTOBUF_LIBRARY ${PROTOBUF_ROOT}/lib/libprotobuf.so)

include_directories(${PROTOBUF_INCLUDE_DIR})

# ==============================
# 生成目录
# ==============================
set(GENERATED_PROTO_DIR ${CMAKE_BINARY_DIR}/src)

file(MAKE_DIRECTORY ${GENERATED_PROTO_DIR})

# ------------------------------------------------
# 所有proto
# ------------------------------------------------

set(PROTO_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/topology_change.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/dag_conf.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/proto_desc.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/choreography_conf.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/record.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/component_conf.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/cyber_conf.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/perf_conf.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/classic_conf.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/parameter.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/unit_test.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/scheduler_conf.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/transport_conf.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/qos_profile.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/run_mode_conf.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/role_attributes.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/clock.proto
)

# 保存所有生成文件
set(PROTO_SRCS)
set(PROTO_HDRS)

# ==============================
# 遍历proto生成代码
# ==============================
foreach(PROTO_FILE ${PROTO_FILES})

    file(RELATIVE_PATH REL_PROTO_PATH
        ${CMAKE_SOURCE_DIR}/src
        ${PROTO_FILE}
    )

    get_filename_component(PROTO_DIR ${REL_PROTO_PATH} DIRECTORY)
    get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)

    set(PROTO_SRC ${GENERATED_PROTO_DIR}/${PROTO_DIR}/${PROTO_NAME}.pb.cc)
    set(PROTO_HDR ${GENERATED_PROTO_DIR}/${PROTO_DIR}/${PROTO_NAME}.pb.h)

    add_custom_command(
        OUTPUT ${PROTO_SRC} ${PROTO_HDR}
        COMMAND ${CMAKE_COMMAND} -E env
            LD_LIBRARY_PATH=${PROTOBUF_LIB_DIR}
            ${PROTOC_EXECUTABLE}
        ARGS
            --cpp_out=${GENERATED_PROTO_DIR}
            -I ${CMAKE_SOURCE_DIR}/src
            ${PROTO_FILE}
        DEPENDS ${PROTO_FILE}
        COMMENT "Generating protobuf source from ${PROTO_FILE}"
    )

    list(APPEND PROTO_SRCS ${PROTO_SRC})
    list(APPEND PROTO_HDRS ${PROTO_HDR})

endforeach()

add_custom_target(generate_cyber_proto ALL
    DEPENDS ${PROTO_SRCS} ${PROTO_HDRS}
)

# ------------------------------------------------
# 生成proto库
# ------------------------------------------------

add_library(cyber_proto SHARED 
    ${PROTO_SRCS}
)

target_include_directories(cyber_proto
    PUBLIC
        ${GENERATED_PROTO_DIR}
        ${PROTOBUF_INCLUDE_DIR}
)

target_link_libraries(cyber_proto
    PUBLIC
        ${PROTOBUF_LIB}
)