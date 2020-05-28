package(
    default_visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "logger_async",
    srcs = ["logger_async.cc"],
    hdrs = ["logger_async.h"],
    deps = [
        ":base",
        "@com_google_absl//absl/synchronization",
        "@com_google_glog//:glog",
    ],
)

cc_library(
    name = "logging",
    srcs = ["logging.cc"],
    hdrs = ["logging.h"],
    deps = [
        ":base",
        ":logger_async",
        "@com_google_absl//absl/strings",
        "@com_google_glog//:glog",
        "@com_google_absl//absl/time",
    ],
)

cc_library(
    name = "base",
    srcs = [],
    hdrs = [
        "spin_lock.h",
        "macros.h"
    ],
    deps = [
        "@com_google_absl//absl/base",
    ],
)

cc_test(
    name = "logging_test",
    srcs = ["logging_test.cc"],
    deps = [
        ":logging",
        "//src/base/test:test_main",
        "@com_google_googletest//:gtest",
        "//src/base/test:test_util",
    ],
)

cc_library(
    name = "scoped_cleanup",
    srcs = [],
    hdrs = ["scoped_cleanup.h"],
    deps = [
        ":base",
    ],
)

cc_test(
    name = "scoped_cleanup_test",
    srcs = ["scoped_cleanup_test.cc"],
    deps = [
        ":scoped_cleanup",
        "//src/base/test:test_main",
    ]
)


