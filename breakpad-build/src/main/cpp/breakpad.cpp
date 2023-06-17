#include "breakpad.h"
#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/minidump_descriptor.h"

bool DumpCallback(const google_breakpad::MinidumpDescriptor &descriptor,
                  void *context,
                  bool succeeded) {
    return succeeded;
}

void initBreakpad(const char *path) {
    google_breakpad::MinidumpDescriptor descriptor(path);
    google_breakpad::ExceptionHandler eh(descriptor, nullptr, DumpCallback,
                                         nullptr, true, -1);
}