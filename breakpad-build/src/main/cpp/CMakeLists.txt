# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Declares and names the project.

project("breakpad")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
set(GOOGLE_BREAKPAD_DIR "${PROJECT_SOURCE_DIR}/../../../../breakpad")
message("GOOGLE_BREAKPAD_DIR == ${PROJECT_SOURCE_DIR}")
message("GOOGLE_BREAKPAD_DIR == ${GOOGLE_BREAKPAD_DIR}")

add_definitions(-D_GIT_BREAKPAD=\"${GIT_BREAKPAD}\")

IF (CMAKE_SYSTEM_NAME MATCHES "iOS")
        ADD_DEFINITIONS(-DUSE_PROTECTED_ALLOCATIONS=0)
#        复制于breakpad/src/client/ios工程
        set(SOURCE_FILE
                #                "${GOOGLE_BREAKPAD_DIR}/src/client/ios/Breakpad.mm"
                "${GOOGLE_BREAKPAD_DIR}/src/client/mac/crash_generation/ConfigFile.mm"
                "${GOOGLE_BREAKPAD_DIR}/src/client/mac/handler/breakpad_nlist_64.cc"
                "${GOOGLE_BREAKPAD_DIR}/src/client/mac/handler/dynamic_images.cc"
                "${GOOGLE_BREAKPAD_DIR}/src/client/mac/handler/exception_handler.cc"
                "${GOOGLE_BREAKPAD_DIR}/src/client/mac/handler/minidump_generator.cc"
                "${GOOGLE_BREAKPAD_DIR}/src/client/mac/handler/protected_memory_allocator.cc"
                #            "${GOOGLE_BREAKPAD_DIR}/src/client/mac/sender/uploader.mm"
                "${GOOGLE_BREAKPAD_DIR}/src/common/long_string_dictionary.cc"
                "${GOOGLE_BREAKPAD_DIR}/src/client/minidump_file_writer.cc"
                "${GOOGLE_BREAKPAD_DIR}/src/common/convert_UTF.cc"
                #            "${GOOGLE_BREAKPAD_DIR}/src/common/mac/GTMLogger.m"
                #            "${GOOGLE_BREAKPAD_DIR}/src/common/mac/HTTPMultipartUpload.m"
                "${GOOGLE_BREAKPAD_DIR}/src/common/mac/file_id.cc"
                "${GOOGLE_BREAKPAD_DIR}/src/common/mac/macho_id.cc"
                "${GOOGLE_BREAKPAD_DIR}/src/common/mac/macho_utilities.cc"
                "${GOOGLE_BREAKPAD_DIR}/src/common/mac/macho_walker.cc"
                "${GOOGLE_BREAKPAD_DIR}/src/common/mac/string_utilities.cc"
                "${GOOGLE_BREAKPAD_DIR}/src/common/md5.cc"
                "${GOOGLE_BREAKPAD_DIR}/src/common/string_conversion.cc"
                #            "${GOOGLE_BREAKPAD_DIR}/src/client/ios/handler/ios_exception_minidump_generator.mm"
                #                "${GOOGLE_BREAKPAD_DIR}/src/client/ios/BreakpadController.mm"
                "${GOOGLE_BREAKPAD_DIR}/src/common/simple_string_dictionary.cc"
                )
        add_library(
                breakpad
                STATIC
                ${SOURCE_FILE}
                isDebuggerActive.cpp)
        target_include_directories(breakpad
                PUBLIC
                ${GOOGLE_BREAKPAD_DIR}/src
                ${GOOGLE_BREAKPAD_DIR}/src/third_party/musl/include
                ./
                )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
        include_directories(${GOOGLE_BREAKPAD_DIR}/src ${GOOGLE_BREAKPAD_DIR}/src/common/android/include)

        set(LINUX_SYSCALL_SUPPORT_DIR "${PROJECT_SOURCE_DIR}/../../../../linux-syscall-support")
        file(COPY ${LINUX_SYSCALL_SUPPORT_DIR}/linux_syscall_support.h DESTINATION "${PROJECT_SOURCE_DIR}/../../../build/linux-syscall-support/third_party/lss")
        include_directories("${PROJECT_SOURCE_DIR}/../../../build/linux-syscall-support")
        #        ENABLE_LANGUAGE(ASM)
        file(GLOB GOOGLE_BREAKPAD_SOURCE
                ${GOOGLE_BREAKPAD_DIR}/src/client/linux/crash_generation/crash_generation_client.cc
                ${GOOGLE_BREAKPAD_DIR}/src/client/linux/dump_writer_common/thread_info.cc
                ${GOOGLE_BREAKPAD_DIR}/src/client/linux/dump_writer_common/ucontext_reader.cc
                ${GOOGLE_BREAKPAD_DIR}/src/client/linux/handler/exception_handler.cc
                ${GOOGLE_BREAKPAD_DIR}/src/client/linux/handler/minidump_descriptor.cc
                ${GOOGLE_BREAKPAD_DIR}/src/client/linux/log/log.cc
                ${GOOGLE_BREAKPAD_DIR}/src/client/linux/microdump_writer/microdump_writer.cc
                ${GOOGLE_BREAKPAD_DIR}/src/client/linux/minidump_writer/linux_dumper.cc
                ${GOOGLE_BREAKPAD_DIR}/src/client/linux/minidump_writer/linux_ptrace_dumper.cc
                ${GOOGLE_BREAKPAD_DIR}/src/client/linux/minidump_writer/minidump_writer.cc
                ${GOOGLE_BREAKPAD_DIR}/src/client/linux/minidump_writer/pe_file.cc
                ${GOOGLE_BREAKPAD_DIR}/src/client/minidump_file_writer.cc
                ${GOOGLE_BREAKPAD_DIR}/src/common/convert_UTF.cc
                ${GOOGLE_BREAKPAD_DIR}/src/common/md5.cc
                ${GOOGLE_BREAKPAD_DIR}/src/common/string_conversion.cc
                ${GOOGLE_BREAKPAD_DIR}/src/common/linux/breakpad_getcontext.S
                ${GOOGLE_BREAKPAD_DIR}/src/common/linux/elfutils.cc
                ${GOOGLE_BREAKPAD_DIR}/src/common/linux/file_id.cc
                ${GOOGLE_BREAKPAD_DIR}/src/common/linux/guid_creator.cc
                ${GOOGLE_BREAKPAD_DIR}/src/common/linux/linux_libc_support.cc
                ${GOOGLE_BREAKPAD_DIR}/src/common/linux/memory_mapped_file.cc
                ${GOOGLE_BREAKPAD_DIR}/src/common/linux/safe_readlink.cc
                )

        file(GLOB BREAKPAD_ASM_SOURCE ${GOOGLE_BREAKPAD_DIR}/src/common/linux/breakpad_getcontext.S)

        set_source_files_properties(${BREAKPAD_ASM_SOURCE} PROPERTIES LANGUAGE C)

        add_library( # Sets the name of the library.
                breakpad

                # Sets the library as a shared library.
                #        SHARED
                STATIC
                ${GOOGLE_BREAKPAD_SOURCE}
                ${BREAKPAD_ASM_SOURCE}
                # Provides a relative path to your source file(s).
                breakpad.cpp)


        # Searches for a specified prebuilt library and stores the path as a
        # variable. Because CMake includes system libraries in the search path by
        # default, you only need to specify the name of the public NDK library
        # you want to add. CMake verifies that the library exists before
        # completing its build.

        find_library( # Sets the name of the path variable.
                log-lib

                # Specifies the name of the NDK library that
                # you want CMake to locate.
                log)

        # Specifies libraries CMake should link to your target library. You
        # can link multiple libraries, such as libraries you define in this
        # build script, prebuilt third-party libraries, or system libraries.

        target_link_libraries( # Specifies the target library.
                breakpad

                # Links the target library to the log library
                # included in the NDK.
                ${log-lib})
ENDIF (CMAKE_SYSTEM_NAME MATCHES "iOS")