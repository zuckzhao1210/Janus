cmake_minimum_required(VERSION 3.16)
project(janus)
 
# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译方式
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE debug)
endif()

add_subdirectory(src/modules)
add_subdirectory(src/cyber)

# ==============================
# 安装路径
# ==============================
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX
        ${CMAKE_SOURCE_DIR}/install
        CACHE PATH "Install path prefix" FORCE)
endif()

# # 包含第三方库头文件
# include_directories(
#     ${CMAKE_SOURCE_DIR}/thirdparty/include/
#     ${CMAKE_SOURCE_DIR}/src
# )

# file(GLOB SRC_LIST "${CMAKE_SOURCE_DIR}/src/*.cpp")
# file(GLOB PROTO_SRC_LIST "${CMAKE_BINARY_DIR}/src/*.cc")
# # 创建可执行文件
# add_executable(janus ${SRC_LIST} ${PROTO_SRC_LIST})
# # add_executable(apollo_pub src/apollo_pub.cpp)

# # protomodule 头文件
# target_include_directories(janus
#     PUBLIC
#         ${CMAKE_BINARY_DIR}/src
# )
# # 库文件
# link_directories(${CMAKE_SOURCE_DIR}/thirdparty/lib)
# target_link_libraries(janus 
#     fastrtps
#     fastcdr
#     protobuf
#     pthread
#     glog
#     apollo_proto
#     # ${CMAKE_SOURCE_DIR}/thirdparty/lib/libtinyxml2.so
# )

# 测试
add_executable(janus_test src/main.cpp src/Janus.cpp src/apollo_cyber.cpp)
link_directories(${CMAKE_SOURCE_DIR}/thirdparty/lib)
target_link_libraries(janus_test
    ${CMAKE_SOURCE_DIR}/thirdparty/lib/libfastrtps.so.1
    ${CMAKE_SOURCE_DIR}/thirdparty/lib/libfastcdr.so
    ${CMAKE_SOURCE_DIR}/thirdparty/lib/libprotobuf.so
    ${CMAKE_SOURCE_DIR}/thirdparty/lib/libglog.so
    pthread
    apollo_proto
    cyber_node
    cyber_state
    # ${CMAKE_SOURCE_DIR}/thirdparty/lib/libtinyxml2.so
)
