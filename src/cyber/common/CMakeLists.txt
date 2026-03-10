cmake_minimum_required(VERSION 3.16)

project(cyber_common)

# =========================
# 源文件
# =========================
set(CYBER_COMMON_SRCS
    global_data.cc
    file.cc
)

# =========================
# 生成库
# =========================
add_library(cyber_common SHARED
    ${CYBER_COMMON_SRCS}
)

# =========================
# 头文件路径
# =========================
target_include_directories(cyber_common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/thirdparty/include/
)

# =========================
# 依赖库
# =========================
target_link_libraries(cyber_common
    PUBLIC
        cyber_binary
        ${CMAKE_SOURCE_DIR}/thirdparty/lib/libprotobuf.so
        glog
)
