#!/usr/bin/env bash

# Build the project
cd build
cmake ..
cmake --build .
valgrind ./VCompiler /home/jesus/code/VCompiler/index.vv
