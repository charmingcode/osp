workspace(name = "com_github_osp")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# GoogleTest/GoogleMock framework.
http_archive(
    name = "com_google_googletest",
    sha256 = "54a139559cc46a68cf79e55d5c22dc9d48e647a66827342520ce0441402430fe",
    strip_prefix = "googletest-1.10.x",
    # Lastest snapshot at 2019-10-03
    urls = [
        "https://github.com/google/googletest/archive/v1.10.x.zip",
    ],
)

# Google logging and flags library.
http_archive(
    name = "com_github_gflags_gflags",
    strip_prefix = "gflags-2.2.2",
    urls = [
        "https://mirror.bazel.build/github.com/gflags/gflags/archive/v2.2.2.tar.gz",
        "https://github.com/gflags/gflags/archive/v2.2.2.tar.gz",
    ],
)

http_archive(
    name = "com_google_glog",
    #patches = [
    #      "@//third_party/glog:glog.patch"
    #],
    sha256 = "f28359aeba12f30d73d9e4711ef356dc842886968112162bc73002645139c39c",
    strip_prefix = "glog-0.4.0",
    urls = [
        "https://mirror.bazel.build/github.com/google/glog/archive/v0.4.0.tar.gz",
        "https://github.com/google/glog/archive/v0.4.0.tar.gz",
    ],
)

# Google Abseil C++ Library
http_archive(
    name = "com_google_absl",
    sha256 = "a5a667e6899aa6767cd9bb24ca5afe6e51ba719862a810f30ad39bb256cfe17f",
    strip_prefix = "abseil-cpp-a2e6adecc294dc4cd98cc285a9134ce58e0f2ad0",
    # Snapshot as of 2020-01-21
    urls = [
        "https://github.com/abseil/abseil-cpp/archive/a2e6adecc294dc4cd98cc285a9134ce58e0f2ad0.zip",
    ],
)

# Google grpc
# update library version from https://packages.grpc.io/
http_archive(
    name = "com_github_grpc_grpc",
    sha256 = "dc4c42a431ca97eed7f23528861d938244d7defd3a466f9d1a763bff9bdc1e1c",
    strip_prefix = "grpc-bebd20b126303a1f5d6cbb31d0463460b59c5074",
    urls = [
        "https://github.com/grpc/grpc/archive/bebd20b126303a1f5d6cbb31d0463460b59c5074.tar.gz",
    ],
)

# Required for dependency @com_github_grpc_grpc
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()
