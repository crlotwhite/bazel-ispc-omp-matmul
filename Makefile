.PHONY: all clean run

# Add .exe extension on Windows
ifeq ($(OS),Windows_NT)
EXEEXT := .exe
else
EXEEXT :=
endif

ifeq ($(OS),Windows_NT)
RC := --bazelrc=win.rc
else
ifeq ($(OS),Darwin)
RC := --bazelrc=mac.rc
else
RC :=
endif
endif

all: clean build run

build:
	bazel $(RC) build //main:main

clean:
	bazel clean

run:
	bazel-bin/main/main$(EXEEXT)