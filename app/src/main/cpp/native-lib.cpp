#include <jni.h>
#include <string>

#include "XLog.h"
#include "FFPlayerBuilder.h"
#include <android/native_window_jni.h>

static IPlayer *player = nullptr;

IVideoView *videoView = nullptr;

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

    FFPlayerBuilder::InitHard(vm);
    player = FFPlayerBuilder::Get()->BuilderPlayer();
    player->Open("/sdcard/tencent/QQfile_recv/v1080.mp4");
    player->Start();
    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_zaozao_hplayer_XPlay_initView(JNIEnv *env, jobject instance, jobject surface) {

    ANativeWindow *nativeWindow = ANativeWindow_fromSurface(env, surface);
    if (player) {
        player->InitView(nativeWindow);
    }
}