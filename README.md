# mac上编译FFmpeg源码记录
build_android.sh 无敌脚本 
```

#!/bin/bash
NDK=/Users/tracyliu/android-ndk-r17c
SYSROOT=$NDK/platforms/android-21/arch-arm
ISYSROOT=$NDK/sysroot
ASM=$ISYSROOT/usr/include/arm-linux-androideabi
TOOLCHAIN=$NDK/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64
PREFIX=$(pwd)/android/armv7-a
CROSS_PREFIX=$TOOLCHAIN/bin/arm-linux-androideabi-
build_android()
{
    ./configure \
    --prefix=$PREFIX \
    --enable-shared \
    --disable-static \
    --disable-doc \
    --disable-ffmpeg \
    --disable-ffplay \
    --disable-ffprobe \
    --disable-avdevice \
    --disable-symver \
    --cross-prefix=$CROSS_PREFIX \
    --target-os=android \
    --arch=arm \
    --enable-cross-compile \
    --sysroot=$SYSROOT \
    --extra-cflags="-I$ASM -isysroot $ISYSROOT -D__ANDROID_API__=21 -Os -fpic -marm -march=armv7-a"
    make clean
    make
    make install
}
build_android
```


生成的so的位置在 当前目录下 android/armv7-a



---
坑
#### 1.C compiler test failed.
```
/Users/tracyliu/Library/Android/sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gcc is unable to create an executable file.
C compiler test failed.
```

用android-ndk-r17c可以解决


#### 2.config not found

```
WARNING: /Users/tracyliu/android-ndk-r17c/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-pkg-config not found, library detection may fail.
```
忽略即可

---
##### CMAKE_SOURCE_DIR的作用
它指向的是最顶层CMakeLists.txt所在的文件夹的路径。

[Are CMAKE_SOURCE_DIR and PROJECT_SOURCE_DIR the same in CMake?](https://stackoverflow.com/questions/32028667/are-cmake-source-dir-and-project-source-dir-the-same-in-cmake)

CmakeList.txt

```
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

#set(CURRENT_DIR ${PROJECT_SOURCE_DIR})
set(CURRENT_DIR "/Users/tracyliu/GitHub/FFmpegDemo/app")
#/Users/tracyliu/Desktop/MutipleMedia/TesJNI/app/src/main/cpp



#在Gradle Console输出信息
#CMAKE_SOURCE_DIR: E:/MyApplication2/app
message("CURRENT_DIR:" ${PROJECT_SOURCE_DIR})
#PROJECT_SOURCE_DIR

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

#[[find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)]]

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
#[[
target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})]]


include_directories(${CURRENT_DIR}/src/main/cpp/include)
add_library(avcodec SHARED IMPORTED)
set_target_properties( avcodec
        PROPERTIES
        IMPORTED_LOCATION ${CURRENT_DIR}/src/main/jniLibs/armeabi-v7a/libavcodec.so)
add_library(avformat SHARED IMPORTED)
set_target_properties( avformat
        PROPERTIES
        IMPORTED_LOCATION ${CURRENT_DIR}/src/main/jniLibs/armeabi-v7a/libavformat.so)
add_library(avfilter SHARED IMPORTED)
set_target_properties( avfilter
        PROPERTIES
        IMPORTED_LOCATION ${CURRENT_DIR}/src/main/jniLibs/armeabi-v7a/libavfilter.so )
add_library(avutil SHARED IMPORTED)
set_target_properties( avutil
        PROPERTIES
        IMPORTED_LOCATION ${CURRENT_DIR}/src/main/jniLibs/armeabi-v7a/libavutil.so )
add_library(swresample SHARED IMPORTED)
set_target_properties( swresample
        PROPERTIES
        IMPORTED_LOCATION ${CURRENT_DIR}/src/main/jniLibs/armeabi-v7a/libswresample.so )
add_library(swscale SHARED IMPORTED)
set_target_properties( swscale
        PROPERTIES
        IMPORTED_LOCATION ${CURRENT_DIR}/src/main/jniLibs/armeabi-v7a/libswscale.so )

target_link_libraries( # Specifies the target library.
        native-lib
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        avcodec
        avformat
        avfilter
        avutil
        swresample
        swscale
        )
```



[在Mac上编译基于Android平台的FFmpeg源码](https://codezjx.com/2019/06/21/compile-ffmpeg-android/)