.PHONY: all clean

all: clean build run

build:
	bazel build //main:main

clean:
	bazel clean

run:
	bazel-bin/main/main