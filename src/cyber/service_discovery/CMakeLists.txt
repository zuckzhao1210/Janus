cmake_minimum_required(VERSION 3.16)

project(cyber_service_discovery)

set(CMAKE_CXX_STANDARD 14)

# ==============================
# cyber_service_discovery
# ==============================

add_library(cyber_service_discovery SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/topology_manager.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/communication/participant_listener.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/communication/subscriber_listener.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/container/graph.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/container/multi_value_warehouse.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/container/single_value_warehouse.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/specific_manager/channel_manager.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/specific_manager/manager.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/specific_manager/node_manager.cc
    # ${CMAKE_CURRENT_SOURCE_DIR}/specific_manager/service_manager.cc
)

target_include_directories(cyber_service_discovery
PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/thirdparty/include
)

target_link_libraries(cyber_service_discovery
PUBLIC
    cyber_transport
    cyber_common
    # cyber_binary
    role_attributes_cc_proto
    fastrtps
    cyber_state
    cyber_message
    proto_desc_cc_proto
    topology_change_cc_proto
    cyber_time
)

# ==============================
# cyber_service_discovery_role
# ==============================

add_library(cyber_service_discovery_role SHARED
    role/role.cc
)

target_include_directories(cyber_service_discovery
PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/thirdparty/include
)

target_link_libraries(cyber_service_discovery_role
PUBLIC
    cyber_binary
    cyber_common
    cyber_proto
)