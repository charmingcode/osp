cmake_minimum_required(VERSION 3.18)

project(osp_demo VERSION 1.0.1)

# 因为spdlog是基于c++11的库
# set(CMAKE_CXX_STANDARD 11)

########################################
# Third Party
########################################
include(FetchContent)

# gooletest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/gtest # 指定库下载地址
)

FetchContent_MakeAvailable(googletest) # CMake 3.14+

# glog
FetchContent_Declare(
  googlelog
  GIT_REPOSITORY https://github.com/google/glog.git
  GIT_TAG        v0.5.0 
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glog # 指定库下载地址
)

FetchContent_MakeAvailable(googlelog)


# # gRPC
# FetchContent_Declare(
#     gRPC
#     GIT_REPOSITORY https://github.com/grpc/grpc
#     GIT_TAG        v1.28.1
# )
# set(BENCHMARK_ENABLE_TESTING OFF CACHE INTERNAL "")
# set(gRPC_BUILD_TESTS OFF CACHE INTERNAL "")

# FetchContent_MakeAvailable(gRPC)

# # After using add_subdirectory, we can now use the grpc targets directly from
# # this build.
# set(_PROTOBUF_LIBPROTOBUF libprotobuf)
# set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
# set(_GRPC_GRPCPP_UNSECURE grpc++_unsecure)
# set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)


# # Generated sources
# set(_PROTO_SRCS "")
# set(_GRPC_SRCS "")
# set(_PROTO_OUTPUT ${PROJECT_BINARY_DIR}/output/proto)
# file(GLOB PROTO_FILES ${PROJECT_SOURCE_DIR}/proto/*.proto)
# foreach(_proto_file ${PROTO_FILES})
#     # message("${_proto_file}")
#     get_filename_component(_proto_file "${_proto_file}" ABSOLUTE)
#     get_filename_component(_proto_file_path "${_proto_file}" PATH)
#     get_filename_component(_proto_file_name "${_proto_file}" NAME_WE)
#     set(_proto_src "${_PROTO_OUTPUT}/${_proto_file_name}.pb.cc")
#     set(_proto_hdr "${_PROTO_OUTPUT}/${_proto_file_name}.pb.h")
#     set(_grpc_src "${_PROTO_OUTPUT}/${_proto_file_name}.grpc.pb.cc")
#     set(_grpc_hdr "${_PROTO_OUTPUT}/${_proto_file_name}.grpc.pb.h")
#     # message("${_proto_src}")
#     add_custom_command(
#         OUTPUT "${_proto_src}" "${_proto_hdr}" "${_grpc_src}" "${_grpc_hdr}"
#         COMMAND ${_PROTOBUF_PROTOC}
#         ARGS  --grpc_out "${_PROTO_OUTPUT}"
#             --cpp_out "${_PROTO_OUTPUT}"
#             -I "${_proto_file_path}"
#             --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
#             "${_proto_file}"
#         DEPENDS "${_proto_file}"
#     )
#     list(APPEND _PROTO_SRCS "${_proto_src}")
#     list(APPEND _GRPC_SRCS "${_grpc_src}")
# endforeach()

########################################
# Source files
########################################
# file(GLOB SOURCES
#     ${PROJECT_SOURCE_DIR}/src/*.cpp
# )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(src)