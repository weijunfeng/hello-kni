
pluginManagement {
    resolutionStrategy {
        eachPlugin {
            if (requested.id.id == "org.jetbrains.kotlin.multiplatform") {
                useModule("org.jetbrains.kotlin:kotlin-gradle-plugin:1.8.22")
            }
            if (requested.id.id == "com.android.application") {
                useModule("com.android.tools.build:gradle:${requested.version}")
            }
        }
    }

    repositories {
        mavenLocal()
        google()
        mavenCentral()
//        maven("https://dl.bintray.com/kotlin/kotlin-dev")
//        maven("https://dl.bintray.com/kotlin/kotlin-eap")
        gradlePluginPortal()
    }
}
include(":app", ":nativeLib")

include(":protobuf-build")
include(":breakpad-build")
//include(":androidNativeActivity")
