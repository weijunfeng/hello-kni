echo "======$TOOLCHAIN====="
cmake -B build -G Xcode -DCMAKE_CXX_FLAGS=-std=c++17 -DCMAKE_TOOLCHAIN_FILE=../../../breakpad-cmake/ios.toolchain.cmake -DPLATFORM=OS64
cmake --build build --config Release

