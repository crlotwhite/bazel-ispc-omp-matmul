load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

# Detect Windows for toolchain-agnostic flag selection
config_setting(
    name = "is_windows",
    values = {"cpu": "x64_windows"},
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        "//cpu:matmul",
        "//omp:matmul",
        "//matutils:matutils",
        "//timeutils:timeutils",
    ],
    copts = select({
        ":is_windows": ["/openmp"],
        "//conditions:default": ["-fopenmp"],
    }),
    linkopts = select({
        ":is_windows": [],
        "//conditions:default": ["-fopenmp"],
    }),
)
