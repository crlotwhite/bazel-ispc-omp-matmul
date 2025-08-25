load("@rules_cc//cc:cc_library.bzl", "cc_library")

# Detect Windows to pass the correct OpenMP flags (/openmp for MSVC).
config_setting(
    name = "is_windows",
    values = {"cpu": "x64_windows"},
)

cc_library(
    name = "matmul",
    srcs = ["matmul.cc"],
    hdrs = ["matmul.h"],
    copts = select({
        ":is_windows": ["/openmp"],
        "//conditions:default": ["-fopenmp"],
    }),
    linkopts = select({
        ":is_windows": [],  # MSVC doesn't need extra link flags for OpenMP
        "//conditions:default": ["-fopenmp"],
    }),
    visibility = ["//main:__pkg__"],
    deps = ["//matutils:matutils"],
)
