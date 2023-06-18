//
// Created by weijunfeng on 2023/6/17.
//

#ifndef HELLO_KNI_BREAKPAD_H
#define HELLO_KNI_BREAKPAD_H

/**
 * 初始化breakpad
 * @param dmpDir 崩溃文件保存路径, 必须保证文件目录存在
 * @return true 初始化成功, false 初始化失败
 */
bool initBreakpad(const char *dmpDir);

#endif //HELLO_KNI_BREAKPAD_H
