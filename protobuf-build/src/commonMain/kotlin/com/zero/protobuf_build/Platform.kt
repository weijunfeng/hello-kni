package com.zero.protobuf_build

interface Platform {
    val name: String
}

expect fun getPlatform(): Platform