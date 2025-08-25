load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "matutils",
    srcs = ["utils.cc"],
    hdrs = ["utils.h"],
    visibility = [
        "//main:__pkg__",
        "//cpu:__pkg__",
        "//omp:__pkg__",
    ],
)
