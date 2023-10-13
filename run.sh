#!/usr/bin/env bash

# Build the project
mkdir build
cd build
cmake ..
cmake --build .
./VCompiler ../index.vv
