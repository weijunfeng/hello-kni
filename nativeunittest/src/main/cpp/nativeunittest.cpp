#include <jni.h>
#include <string>
#include <iostream>
#include <fstream>

#include <sys/stat.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>


std::string formatSize(long long int size) {
    static const char *suffixes[] = {"B", "KB", "MB", "GB", "TB"};
    if (size <= 0) {
        return "0 B";
    }
    std::string result;
    int suffixIndex = 0;


    auto doubleSize = static_cast<double>(size);
    while (doubleSize > 1024 && suffixIndex < 4) {
        doubleSize /= 1024;
        ++suffixIndex;
    }

    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << doubleSize;
    ss >> result;
    result += " ";
    result += suffixes[suffixIndex];
    return result;
}

long long int getFileSize(const char *filename) {
    struct stat fileStat{};
    if (stat(filename, &fileStat) == 0) {
        return fileStat.st_size;
    }
    return -1;  // 获取文件大小失败
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_zero_nativeunittest_NativeLib_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = formatSize(
            getFileSize("/data/user/0/com.zero.nativeunittest.test/files/2季度总结与3季度计划.pptx"));
    return env->NewStringUTF(hello.c_str());
}

