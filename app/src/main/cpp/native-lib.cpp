#include <jni.h>
#include <string>

#include "FFDemux.h"
#include "XLog.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_zaozao_hplayer_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    IDemux *de = new FFDemux();
    de->Open("/sdcard/DCIM/Camera/VID_20180215_142837.mp4");
    de->Start();
    XSleep(3000);
    de->Stop();
    return env->NewStringUTF(hello.c_str());
}
