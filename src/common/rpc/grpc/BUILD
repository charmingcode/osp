
# Bazel has native cc_proto_library rule, but it does not have cc_grpc_library. 
# this rule (cc_grpc_library) in this repo seems like the best candidate to be 
# "that" rule.
# This change makes possible using cc_grpc_library to generate only grpc library, 
# and consume protobuf portion as dependencies. The typical BUILD.bazel file 
# configuration now should look like the following:

# proto_library(
#    name = "my_proto",
#    srcs = ["my.proto"],
#  )

# cc_proto_library(
#    name = "my_cc_proto",
#    deps = [":my_proto"]
# )

# cc_grpc_library(
#     name = "my_cc_grpc",
#     srcs = [":my_proto"],
#     deps = [":my_cc_proto"]
#     grpc_only = True,
# )

load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

package(
    default_visibility = [
        "//visibility:private",
    ],
)

cc_binary(
    name = 'greeter_client_test',
    srcs = ['greeter_client_test.cc'],
    deps = [
        ':helloworld_cc_grpc',
        '@com_github_grpc_grpc//:grpc++',
    ],
    linkopts = ['-ldl'],
)

cc_binary(
    name = 'greeter_server_test',
    srcs = ['greeter_server_test.cc'],
    deps = [
        ':helloworld_cc_grpc',
        '@com_github_grpc_grpc//:grpc++',
    ],
    linkopts = ['-ldl'],
)

cc_grpc_library(
    name = "helloworld_cc_grpc",
    srcs = [":helloworld_proto"],
    grpc_only = True,
    deps = [":helloworld_cc_proto"],
)

cc_proto_library(
    name = "helloworld_cc_proto",
    deps = [":helloworld_proto"],
)

proto_library(
    name = 'helloworld_proto',
    srcs = ['helloworld_test.proto'],
)