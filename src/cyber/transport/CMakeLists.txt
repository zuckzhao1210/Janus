cmake_minimum_required(VERSION 3.16)

project(cyber_transport)

set(CMAKE_CXX_STANDARD 14)

# ==============================
# cyber_service_discovery
# ==============================

add_library(cyber_transport SHARED
    
)

target_include_directories(cyber_transport
PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/thirdparty/include
)

target_link_libraries(cyber_transport
PUBLIC
    cyber_service_discovery_role
    cyber_common
    cyber_proto
    cyber_message
    cyber_event
    fastrtps
)
