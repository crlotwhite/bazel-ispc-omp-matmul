load("@rules_ispc//:ispc.bzl", "ispc_cc_library")
load("@rules_cc//cc:cc_library.bzl", "cc_library")

# ISPC library target
ispc_cc_library(
    name = "matmul_ispc",
    srcs = ["matmul.ispc"],
    out = "matmul_ispc.h",
    ispc_main_source_file = "matmul.ispc",
)

# C++ wrapper library
cc_library(
    name = "matmul",
    srcs = ["matmul.cc"],
    hdrs = ["matmul.h"],
    deps = [
        ":matmul_ispc",
        "//matutils:matutils",
    ],
    visibility = ["//main:__pkg__"],
)
