cmake_minimum_required(VERSION 3.16)

project(apollo_proto)

# ==============================
# 模块名称
# ==============================
set(MODULE_NAME apollo_proto)

# ==============================
# protobuf thirdparty路径
# ==============================
set(PROTOBUF_ROOT ${CMAKE_SOURCE_DIR}/thirdparty)

set(PROTOC_EXECUTABLE ${PROTOBUF_ROOT}/protoc)
set(PROTOBUF_INCLUDE_DIR ${PROTOBUF_ROOT}/include)
set(PROTOBUF_LIB_DIR ${PROTOBUF_ROOT}/lib)
set(PROTOBUF_LIBRARY ${PROTOBUF_ROOT}/lib/libprotobuf.so)

# ==============================
# proto文件列表
# ==============================
set(PROTO_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/common_msgs/basic_msgs/geometry.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/common_msgs/basic_msgs/error_code.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/common_msgs/basic_msgs/vehicle_id.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/common_msgs/basic_msgs/drive_state.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/common_msgs/basic_msgs/header.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/common_msgs/basic_msgs/pnc_point.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/common_msgs/basic_msgs/vehicle_signal.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/common_msgs/chassis_msgs/chassis.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/common_msgs/control_msgs/input_debug.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/common_msgs/control_msgs//pad_msg.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/common_msgs/control_msgs/control_cmd.proto
)

# ==============================
# 生成目录
# ==============================
set(GENERATED_PROTO_DIR ${CMAKE_BINARY_DIR}/src/)

file(MAKE_DIRECTORY ${GENERATED_PROTO_DIR})

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

add_custom_target(generate_proto ALL
    DEPENDS ${PROTO_SRCS} ${PROTO_HDRS}
)

# ==============================
# 生成动态库
# ==============================
add_library(${MODULE_NAME} SHARED
    ${PROTO_SRCS}
)

# ==============================
# include目录导出
# ==============================
target_include_directories(${MODULE_NAME}
    PUBLIC
        ${PROTOBUF_INCLUDE_DIR}
        ${GENERATED_PROTO_DIR}
)

# ==============================
# 链接protobuf
# ==============================
target_link_libraries(${MODULE_NAME}
    PUBLIC
        ${PROTOBUF_LIBRARY}
)

# ==============================
# RPATH设置
# ==============================
set_target_properties(${MODULE_NAME} PROPERTIES
    BUILD_RPATH ${PROTOBUF_ROOT}/lib
)

# ==============================
# install
# ==============================
install(TARGETS ${MODULE_NAME}
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${GENERATED_PROTO_DIR}/
    DESTINATION include
    FILES_MATCHING PATTERN "*.pb.h"
)