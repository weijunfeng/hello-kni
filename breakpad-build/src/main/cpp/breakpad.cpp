#include "breakpad.h"
#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/minidump_descriptor.h"
//#include <filesystem> // c++17 支持
#include <iostream>
#include <fstream>

#include <sys/stat.h>

#include <iostream>
#include <sys/stat.h>

BreakpadCallback globalBreakpadCallback = nullptr;

bool DumpCallback(const google_breakpad::MinidumpDescriptor &descriptor,
                  void *context,
                  bool succeeded) {
    if (globalBreakpadCallback != nullptr) {
        auto dmpFilePath = descriptor.path();
        if (dmpFilePath == nullptr) {
            return globalBreakpadCallback(succeeded, "");
        }
        return globalBreakpadCallback(succeeded, dmpFilePath);
    }
    return succeeded;
}

bool fileExists(const std::string &filePath) {
    struct stat info{};
    if (stat(filePath.c_str(), &info) != 0) {
        return false;
    }
    std::ifstream file(filePath);
    auto fileGood = file.good();
    file.close();
    return fileGood;
}

bool directoryExists(const std::string &directoryPath) {
    if (directoryPath.empty()) {
        return false;
    }
    struct stat info{};
    if (stat(directoryPath.c_str(), &info) != 0) {
        return false; // 目录不存在
    }
    return S_ISDIR(info.st_mode);
}


bool createDirectory(const std::string &path) {
    if (path.empty()) {
        return false;
    }
    if (directoryExists(path)) {
        return true;
    }
    if (mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) == 0 || errno == EEXIST) {
        return true;
    } else {
        return false;
    }
}

bool createDirectories(const std::string &path) {
    if (path.empty()) {
        return false;
    }
    size_t pos = 0;
    while ((pos = path.find('/', pos + 1)) != std::string::npos) {
        std::string subPath = path.substr(0, pos);
        if (!createDirectory(subPath)) {
            return false;
        }
    }
    return createDirectory(path);
}

bool hasInitBreakpad() {
    return globalBreakpadCallback != nullptr;
}

//bool directoryExists(const std::string &path) {
//    //使用 std::filesystem::is_directory() 函数来检查给定路径是否为一个目录。fs::status() 函数用于获取路径的状态信息
//    return std::__fs::filesystem::is_directory(std::__fs::filesystem::status(path));
//}
//
//bool fileExists(const std::string &filePath) {
//    //使用 std::filesystem::exists() 函数来检查给定路径是否存在，并使用 std::filesystem::is_regular_file() 函数来确保路径指向一个常规文件
//    return std::__fs::filesystem::exists(filePath) && std::__fs::filesystem::is_regular_file(filePath);
//}

bool initBreakpad(const char *dmpDir, BreakpadCallback breakpadCallback) {
    try {
        if (!directoryExists(dmpDir) && !createDirectories(dmpDir)) {
            return false;
        }
        globalBreakpadCallback = breakpadCallback;
        static google_breakpad::MinidumpDescriptor descriptor(dmpDir);
        static google_breakpad::ExceptionHandler eh(descriptor, nullptr, DumpCallback,
                                                    nullptr, true, -1);
        return true;
    } catch (const std::exception &exception) {
        return false;
    }
}