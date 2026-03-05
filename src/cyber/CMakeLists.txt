cmake_minimum_required(VERSION 3.16)

project(cyber)

set(CMAKE_CXX_STANDARD 14)

# add_subdirectory(service_discovery)

add_subdirectory(common)
add_subdirectory(proto)
add_subdirectory(time)
add_subdirectory(event)
add_subdirectory(message)


# =========================
# 生成库 cyber_state
# =========================
add_library(cyber_state SHARED
    state.cc
)

target_include_directories(cyber_state
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/thirdparty/include/
)

target_link_libraries(cyber_state
    PUBLIC
        cyber_common
)

# =========================
# 生成库 cyber_binary
# =========================
add_library(cyber_binary SHARED
    binary.cc
)

target_include_directories(cyber_binary
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/thirdparty/include/
)
