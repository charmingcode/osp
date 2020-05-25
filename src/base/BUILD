package(
    default_visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "logging",
    srcs = ["logging.cc"],
    hdrs = ["logging.h"],
    deps = [
        "@com_google_absl//absl/strings",
        "@com_google_glog//:glog",
        "@com_google_absl//absl/time",
    ],
)

cc_library(
    name = "base",
    srcs = [],
    hdrs = ["spin_lock.h"],
    deps = [
        "@com_google_absl//absl/base",
    ],
)

cc_test(
    name = "logging_test",
    srcs = ["logging_test.cc"],
    deps = [
      ":logging",
      "@com_google_googletest//:gtest",
    ],
)


