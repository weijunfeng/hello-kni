import com.google.protobuf.gradle.id

plugins {
    kotlin("multiplatform")
    kotlin("native.cocoapods")
    id("com.android.library")
    id("com.google.protobuf") version "0.9.3"
    kotlin("plugin.serialization") version "1.8.22"
}

@OptIn(org.jetbrains.kotlin.gradle.ExperimentalKotlinGradlePluginApi::class)
kotlin {
    targetHierarchy.default()

    android {
        compilations.all {
            kotlinOptions {
                jvmTarget = "1.8"
            }
        }
    }
    iosX64()
    iosArm64()
    iosSimulatorArm64()

    cocoapods {
        summary = "Some description for the Shared Module"
        homepage = "Link to the Shared Module homepage"
        version = "1.0"
        ios.deploymentTarget = "14.1"
        framework {
            baseName = "protobuf-build"
        }
    }

    sourceSets {
        val commonMain by getting {
            dependencies {
                //put your multiplatform dependencies here
                implementation("com.google.protobuf:protobuf-kotlin:3.23.3")
                implementation("com.google.protobuf:protobuf-kotlin-lite:3.23.3")
                // 由于 protoc 无法生成全 koltin 代码,可通过序列化插件,把 kotlin 数据序列化为 protobuf 流,在其他层反序列为 proto 数据
                implementation("org.jetbrains.kotlinx:kotlinx-serialization-protobuf:1.5.1")
                // 如果你使用了协程，还需要添加以下依赖
                implementation("org.jetbrains.kotlinx:kotlinx-coroutines-core:1.7.1")

            }
        }
        val commonTest by getting {
            dependencies {
                implementation(kotlin("test"))
            }
        }
    }
}

android {
    namespace = "com.zero.protobuf_build"
    compileSdk = 33
    defaultConfig {
        minSdk = 24
    }
}

afterEvaluate {

}
// 添加 protobuf 插件, https://github.com/google/protobuf-gradle-plugin
protobuf {
    protoc {
//        path =
//            "/Users/zero/Documents/github/工具集/hello-kni/protobuf-build/protoc/protoc-23.3-osx-aarch_64/bin/protoc"
        // 指定 protoc 编译器的版本
        artifact =
            "com.google.protobuf:protoc:3.23.2"// Could not find protoc-3.23.3-osx-aarch_64.exe (com.google.protobuf:protoc:3.23.3).
    }
    generateProtoTasks {
        all().forEach { task ->
            task.builtins {// 解决: protoc: stdout: . stderr: Missing output directives.
                // 必须同时配合--java_out使用 protoc -I=$SRC_DIR --java_out=$DST_DIR --kotlin_out=$DST_DIR $SRC_DIR/*.proto
                id("kotlin") {
                    option("lite")
                }
                id("java") {
                    option("lite")
                }
                id("cpp")
                id("objc")
            }
        }
    }
}