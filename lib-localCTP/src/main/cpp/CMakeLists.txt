# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.4.1)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("localCTP")

#设置so库类型
set(CMAKE_BUILD_TYPE "release")
#设置so库的输出路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../../libs/${ANDROID_ABI})

#format string is not a string literal (potentially insecure) [-Werror,-Wformat-security]
add_definitions(-Wno-format-security)
add_definitions(-D_DEBUG)

include_directories("${PROJECT_SOURCE_DIR}/android")
include_directories("${PROJECT_SOURCE_DIR}/LocalCTP")
include_directories("${PROJECT_SOURCE_DIR}/LocalCTP/ctp_file/current")
include_directories("${PROJECT_SOURCE_DIR}/LocalCTP/auto_generated_code/")
include_directories("${PROJECT_SOURCE_DIR}/LocalCTP/sqlite")
include_directories("${PROJECT_SOURCE_DIR}/TestLocalCTP")

set(static_deps_dir ${PROJECT_SOURCE_DIR}/../../deps)
#add_library(lib-iconv STATIC IMPORTED)
#set_target_properties(lib-iconv PROPERTIES IMPORTED_LOCATION ${static_deps_dir}/lib/${ANDROID_ABI}/libiconv.a)
include_directories("${static_deps_dir}/iconv")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.
add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        android/android_logcat_buf.cpp
        TestLocalCTP/TestLocalCTP.cpp
        LocalCTP/CSqliteHandler.cpp
        LocalCTP/dllmain.cpp
        LocalCTP/LeeDateTime.cpp
        LocalCTP/LocalCTP.cpp
        LocalCTP/LocalTraderApi.cpp
        LocalCTP/Properties.cpp
        LocalCTP/stdafx.cpp
        LocalCTP/auto_generated_code/CTPSQLWrapper.cpp
        LocalCTP/sqlite/shell.c
        LocalCTP/sqlite/sqlite3.c)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        ${static_deps_dir}/lib/${ANDROID_ABI}/libiconv.a
        android
        log)