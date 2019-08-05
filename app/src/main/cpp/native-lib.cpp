#include <jni.h>
#include <string>

/*引用这个ffmpeg的头文件要使用extern "C"。 这是一个坑*/
extern "C" {
#include "libavcodec/avcodec.h"
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_tracyliu_ffmpegdemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    //std::string hello = "Hello from C++";
    std::string hello = avcodec_configuration();
    return env->NewStringUTF(hello.c_str());
}
