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
