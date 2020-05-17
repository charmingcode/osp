workspace(name = "com_charming_osp")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")


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

