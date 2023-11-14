//
// Created by weijunfeng on 2023/6/17.
//

#ifndef HELLO_KNI_BREAKPAD_H
#define HELLO_KNI_BREAKPAD_H

#include <string>

/**
 * breakpad处理回调
 * @param succeeded dmp 指示小型转储文件是否已成功写入
 *
 * @return 是否异常处理结束，如果发生异常并且回调返回 true，Breakpad 会将异常视为已完全处理，从而阻止任何其他处理程序收到异常通知。
 * 如果回调返回 false，Breakpad 会将异常视为未处理，并允许另一个处理程序处理它。如果没有其他处理程序，
 * Breakpad 将向系统报告异常未处理，从而允许调试器或本机崩溃对话框有机会处理异常。
 * 大多数回调实现通常应该返回 |succeeded| 的值，或者当他们不希望报告已处理的异常时返回 false。
 */
typedef bool (*BreakpadCallback)(bool succeeded, const char *dmpFilePath);


/**
 * 获取当前使用的breakpad git版本信息
 * @return 当前使用的breakpad git版本信息
 */
std::string breakpadGit();

/**
 * 是否已经初始化breakpad
 * @return 是否已经初始化breakpad
 */
bool hasInitBreakpad();

/**
 * 初始化breakpad
 * @param dmpDir 崩溃文件保存路径, 必须保证文件目录存在
 * @param breakpadCallback 崩溃处理回调
 * @return true 初始化成功, false 初始化失败
 */
bool initBreakpad(const char *dmpDir, BreakpadCallback breakpadCallback);

#endif //HELLO_KNI_BREAKPAD_H
