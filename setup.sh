#!/bin/bash

rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=~/.vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake
make