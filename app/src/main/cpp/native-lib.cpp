#include <jni.h>
#include <string>

#include "XLog.h"

#include "IPlayProxy.h"
#include <android/native_window_jni.h>


extern "C"
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *res) {


    IPlayProxy::Get()->Init(vm);
    //http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8
    // IPlayProxy::Get()->Open("http://devimages.apple.com.edgekey.net/streaming/examples/bipbop_4x3/gear2/prog_index.m3u8"); //ios测试
    // IPlayProxy::Get()->Open("http://ivi.bupt.edu.cn/hls/cctv6hd.m3u8"); //cctv6
    // IPlayProxy::Get()->Open("http://ivi.bupt.edu.cn/hls/cctv5phd.m3u8"); //cctv5
    // IPlayProxy::Get()->Open("http://ivi.bupt.edu.cn/hls/cctv3hd.m3u8"); //cctv3
    // IPlayProxy::Get()->Open("http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8"); //cctv1


//    IPlayProxy::Get()->Open("/sdcard/DCIM/Camera/VID_20190503_100122.mp4");
//    IPlayProxy::Get()->Start();


//    IPlayProxy::Get()->Open("/sdcard/tencent/QQfile_recv/v1080.mp4");
//    IPlayProxy::Get()->Start();


    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_zaozao_hplayer_XPlay_initView(JNIEnv *env, jobject instance, jobject surface) {

    ANativeWindow *nativeWindow = ANativeWindow_fromSurface(env, surface);
    IPlayProxy::Get()->InitView(nativeWindow);

}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_zaozao_hplayer_PlayActivity_isReady(JNIEnv *env, jobject instance) {
    bool isReady = IPlayProxy::Get()->IsReady();
    return static_cast<jboolean>(isReady);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_zaozao_hplayer_PlayActivity_open(JNIEnv *env, jobject instance, jstring path_) {
    const char *path = env->GetStringUTFChars(path_, nullptr);

    // IPlayProxy::Get()->Open("rtmp://live.hkstv.hk.lxdns.com/live/hks2"); //香港卫视
    IPlayProxy::Get()->Open(path); //香港卫视
    IPlayProxy::Get()->Start();

    env->ReleaseStringUTFChars(path_, path);
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_zaozao_hplayer_PlayActivity_getPlayProgress(JNIEnv *env, jobject instance) {

    return IPlayProxy::Get()->PlayPos();

}extern "C"
JNIEXPORT void JNICALL
Java_com_zaozao_hplayer_XPlay_playOrPause(JNIEnv *env, jobject instance) {

    IPlayProxy::Get()->SetPause(!IPlayProxy::Get()->IsPause());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_zaozao_hplayer_PlayActivity_seek(JNIEnv *env, jobject instance, jdouble pos) {
    IPlayProxy::Get()->Seek(pos);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_zaozao_hplayer_PlayActivity_close(JNIEnv *env, jobject instance) {

    IPlayProxy::Get()->Close();

}