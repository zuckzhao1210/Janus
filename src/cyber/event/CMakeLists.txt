cmake_minimum_required(VERSION 3.16)

project(cyber_event)

set(CYBER_EVENT_SRCS
    perf_event_cache.cc
)

# =========================
# 生成库
# =========================
add_library(cyber_event SHARED
    ${CYBER_EVENT_SRCS}
)

# =========================
# 头文件路径
# =========================
target_include_directories(cyber_event
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

# =========================
# 依赖库
# =========================
target_link_libraries(cyber_event
    PUBLIC
        cyber_common
        cyber_time
        cyber_state
)
