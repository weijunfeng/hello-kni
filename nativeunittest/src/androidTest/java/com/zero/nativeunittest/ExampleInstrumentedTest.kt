package com.zero.nativeunittest

import android.content.Context
import androidx.test.core.app.ApplicationProvider
import androidx.test.ext.junit.runners.AndroidJUnit4
import org.junit.Assert.*
import org.junit.Test
import org.junit.runner.RunWith
import kotlin.math.round

/**
 * Instrumented test, which will execute on an Android device.
 *
 * See [testing documentation](http://d.android.com/tools/testing).
 */
@RunWith(AndroidJUnit4::class)
class ExampleInstrumentedTest {
    fun formatSize(size: Long): String {
        val suffixes = arrayOf("B", "KB", "MB", "GB", "TB")
        var fileSize = size.toDouble()
        var suffixIndex = 0

        while (fileSize > 1024 && suffixIndex < 4) {
            fileSize /= 1024
            suffixIndex++
        }

        return (round(fileSize * 100) / 100).toString() + " " + suffixes[suffixIndex]
    }

    @Test
    fun useAppContext() {
        // Context of the app under test.
        val appContext: Context = ApplicationProvider.getApplicationContext()
        assertEquals("com.zero.nativeunittest.test", appContext.packageName)

        System.loadLibrary("nativeunittest")
        appContext.filesDir.listFiles().forEach {
            println("it.length() = ${formatSize(it.length())}")
        }

        val jni = NativeLib()
        assertEquals("Hello from C++", jni.stringFromJNI())
    }
}