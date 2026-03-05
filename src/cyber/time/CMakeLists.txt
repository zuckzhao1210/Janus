cmake_minimum_required(VERSION 3.16)

project(cyber_time)

set(CYBER_TIME_SRCS
    duration.cc
    time.cc
)

# =========================
# 生成库
# =========================
add_library(cyber_time SHARED
    ${CYBER_TIME_SRCS}
)

# =========================
# 头文件路径
# =========================
target_include_directories(cyber_time
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/thirdparty/include/
)
