cmake_minimum_required(VERSION 3.16)

project(cyber_message)

# =========================
# 源文件
# =========================
set(CYBER_MESSAGE_SRCS
    protobuf_factory.cc
)

# =========================
# 生成库
# =========================
add_library(cyber_message SHARED
    ${CYBER_MESSAGE_SRCS}
)

# =========================
# 头文件路径
# =========================
target_include_directories(cyber_message
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/thirdparty/include/
)

# =========================
# 依赖库
# =========================
target_link_libraries(cyber_message
    PUBLIC
        cyber_common
        cyber_proto
)
