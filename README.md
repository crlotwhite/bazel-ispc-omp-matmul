# Bazel ISPC OMP MatMul

Bazel project implementing MatMul for practice.

There are three modes:

- cpu
- omp (OpenMP)
- ispc (Intel SPMD Program Compiler)

## How to build?

```
make
```

> Before building the project, install the required dependencies: Bazel and ispc.

## Why is the project split into multiple (apparently unnecessary) libraries?

This structure is used to practice working with a complex, multi-library project using Bazel. C++ projects often embed or depend on multiple libraries, so this approach helps rehearse that scenario and learn to use various open-source components.

## Results

### CPU

```
bazel-bin/main/main
MatMul Example
CPU Mode
Matrix multiplication: 310541 ms
mat[0,0] = 34854.5
mat[4095,4095] = 34854.5
```

About 5 minutes.

