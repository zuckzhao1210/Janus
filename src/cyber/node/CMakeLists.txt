cmake_minimum_required(VERSION 3.16)

project(cyber_node)

set(CYBER_NODE_SRCS
    node.cc
)

# =========================
# 生成库
# =========================
add_library(cyber_node SHARED
    ${CYBER_NODE_SRCS}
)

# =========================
# 头文件路径
# =========================
target_include_directories(cyber_node
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/thirdparty/include/
)

# =========================
# 依赖库
# =========================
target_link_libraries(cyber_node
    PUBLIC
        cyber_common
        cyber_proto
        cyber_message
        cyber_time
        cyber_event
        cyber_transport
        cyber_service_discovery
)
