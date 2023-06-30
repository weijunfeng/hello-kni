package com.zero.nativeunittest

class NativeLib {

    /**
     * A native method that is implemented by the 'nativeunittest' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'nativeunittest' library on application startup.
        init {
            System.loadLibrary("nativeunittest")
        }
    }
}