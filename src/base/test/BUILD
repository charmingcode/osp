package(
    default_visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "test_main",
    testonly = 1,
    srcs = ["test_main.cc"],
    deps = [
        "@com_google_glog//:glog",
        "@com_google_googletest//:gtest",
    ],
)

cc_library(
    name = "test_util",
    srcs = ["test_util.cc"],
    hdrs = ["test_util.h"],
    deps = [
        "//src/base:scoped_cleanup",
        "@com_google_glog//:glog",
        "@com_google_googletest//:gtest",
        "@com_google_absl//absl/time",
    ],
)
