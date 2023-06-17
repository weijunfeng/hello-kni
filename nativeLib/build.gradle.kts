import org.jetbrains.kotlin.gradle.plugin.mpp.KotlinNativeTarget
import org.jetbrains.kotlin.gradle.plugin.mpp.NativeBuildType
import org.jetbrains.kotlin.konan.target.KonanTarget.ANDROID_ARM32
import org.jetbrains.kotlin.konan.target.KonanTarget.ANDROID_ARM64
import org.jetbrains.kotlin.konan.target.KonanTarget.ANDROID_X64
import org.jetbrains.kotlin.konan.target.KonanTarget.ANDROID_X86

plugins {
    kotlin("multiplatform")
    id("com.android.library")
}

val jniLibDir = File(project.buildDir, arrayOf("generated", "jniLibs").joinToString(File.separator))

val sharedLib_name_prefix = "knlib"

kotlin {
    android()

    val nativeConfigure: KotlinNativeTarget.() -> Unit = {
        binaries {
            // 指定编译文件为动态库
            sharedLib(sharedLib_name_prefix) {
//                linkTask linkKnlibDebugSharedAndroidNativeArm32.outputFile = hello-kni/nativeLib/build/bin/androidNativeArm32/knlibDebugShared/libknlib.so
//                linkTask linkKnlibReleaseSharedAndroidNativeArm32.outputFile = hello-kni/nativeLib/build/bin/androidNativeArm32/knlibReleaseShared/libknlib.so
//                linkTask linkKnlibDebugSharedAndroidNativeArm64.outputFile = hello-kni/nativeLib/build/bin/androidNativeArm64/knlibDebugShared/libknlib.so
//                linkTask linkKnlibReleaseSharedAndroidNativeArm64.outputFile = hello-kni/nativeLib/build/bin/androidNativeArm64/knlibReleaseShared/libknlib.so
//                linkTask linkKnlibDebugSharedAndroidNativeX86.outputFile = hello-kni/nativeLib/build/bin/androidNativeX86/knlibDebugShared/libknlib.so
//                linkTask linkKnlibReleaseSharedAndroidNativeX86.outputFile = hello-kni/nativeLib/build/bin/androidNativeX86/knlibReleaseShared/libknlib.so
//                linkTask linkKnlibDebugSharedAndroidNativeX64.outputFile = hello-kni/nativeLib/build/bin/androidNativeX64/knlibDebugShared/libknlib.so
//                linkTask linkKnlibReleaseSharedAndroidNativeX64.outputFile = hello-kni/nativeLib/build/bin/androidNativeX64/knlibReleaseShared/libknlib.so
                linkTask.doLast {
                    copy {
                        from(outputFile)

                        val typeName = if (buildType == NativeBuildType.DEBUG) "Debug" else "Release"
                        val abiDirName = when (target.konanTarget) {
                            ANDROID_ARM32 -> "armeabi-v7a"
                            ANDROID_ARM64 -> "arm64-v8a"
                            ANDROID_X86 -> "x86"
                            ANDROID_X64 -> "x86_64"
                            else -> "unknown"
                        }

                        // copy native 编译产物到 android jni 依赖目录下
                        into(file("$jniLibDir/$typeName/$abiDirName"))
                    }
                }

                afterEvaluate {
                    // 连接 android 工程编译和 native工程编译, 否则不会进行 native 工程编译
                    val preBuild by tasks.getting
                    preBuild.dependsOn(linkTask)
                }
            }
        }
        compilations["main"].cinterops {
            val bmpformat by creating
        }
    }

    androidNativeArm32(configure = nativeConfigure)
    androidNativeArm64(configure = nativeConfigure)
    androidNativeX86(configure = nativeConfigure)
    androidNativeX64(configure = nativeConfigure)

    sourceSets {
        val androidNativeArm32Main by getting
        val androidNativeArm64Main by getting
        val androidNativeX86Main by getting
        val androidNativeX64Main by getting

        val nativeMain by creating {
            androidNativeArm32Main.dependsOn(this)
            androidNativeArm64Main.dependsOn(this)
            androidNativeX86Main.dependsOn(this)
            androidNativeX64Main.dependsOn(this)
        }
    }

}

android {
    compileSdk = 33

    defaultConfig {
        minSdk = 23
        targetSdk = 33
        buildConfigField(
            "String",
            "JNI_SHARED_LIB_NAME_PREFIX",
            "\"$sharedLib_name_prefix\""
        )
    }

    sourceSets {
        // 指定 jni 目录
        getByName("debug").jniLibs.srcDirs("$jniLibDir/Debug")
        getByName("release").jniLibs.srcDirs("$jniLibDir/Release")
    }
}
