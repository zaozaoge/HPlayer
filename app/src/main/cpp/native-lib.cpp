#include <jni.h>
#include <string>

#include "XLog.h"

#include "IPlayProxy.h"
#include <android/native_window_jni.h>


extern "C" JNIEXPORT jstring JNICALL
Java_com_zaozao_hplayer_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    //XSleep(3000);
    //de->Stop();
    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *res) {


    IPlayProxy::Get()->Init(vm);
    IPlayProxy::Get()->Open("/sdcard/tencent/QQfile_recv/v1080.mp4");
    IPlayProxy::Get()->Start();
    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_zaozao_hplayer_XPlay_initView(JNIEnv *env, jobject instance, jobject surface) {

    ANativeWindow *nativeWindow = ANativeWindow_fromSurface(env, surface);

    IPlayProxy::Get()->InitView(nativeWindow);

}