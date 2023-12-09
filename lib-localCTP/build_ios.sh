#!/bin/sh
#项目环境配置
export CMAKE=/Applications/CMake.app/Contents/bin
export PATH=$CMAKE:$PATH
touch ~/.bash_profile
source ~/.bash_profile

#构建脚本目录位置
cd "$(dirname "$0")" || exit

mkdir -p "build/ios"

cd build/ios

cmake ../../src/main/cpp -G Xcode  -DCMAKE_CXX_FLAGS=-std=c++14 -DCMAKE_TOOLCHAIN_FILE=../../ios.toolchain.cmake -DPLATFORM=OS64COMBINED

cmake --build . --config Release

cmake --install . --config Release # Necessary to build combined library


cmake ../../src/main/cpp -G Xcode -DCMAKE_CXX_FLAGS=-std=c++14 -DCMAKE_TOOLCHAIN_FILE=../../ios.toolchain.cmake -DPLATFORM=OS64
cmake --build . --config Release