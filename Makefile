.PHONY: all clean run

# Add .exe extension on Windows
ifeq ($(OS),Windows_NT)
EXEEXT := .exe
else
EXEEXT :=
endif

all: clean build run

build:
	bazel build //main:main

clean:
	bazel clean

run:
	bazel-bin/main/main$(EXEEXT)