#include <jni.h>
#include <string>

#include "XLog.h"

#include "IPlayProxy.h"
#include <android/native_window_jni.h>


extern "C" JNIEXPORT jstring JNICALL
Java_com_zaozao_hplayer_PlayActivity_stringFromJNI(
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
    //http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8
   // IPlayProxy::Get()->Open("http://devimages.apple.com.edgekey.net/streaming/examples/bipbop_4x3/gear2/prog_index.m3u8"); //ios测试
   // IPlayProxy::Get()->Open("http://ivi.bupt.edu.cn/hls/cctv6hd.m3u8"); //cctv6
   // IPlayProxy::Get()->Open("http://ivi.bupt.edu.cn/hls/cctv5phd.m3u8"); //cctv5
   // IPlayProxy::Get()->Open("http://ivi.bupt.edu.cn/hls/cctv3hd.m3u8"); //cctv3
   // IPlayProxy::Get()->Open("http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8"); //cctv1
    IPlayProxy::Get()->Open("rtmp://live.hkstv.hk.lxdns.com/live/hks2"); //香港卫视
    IPlayProxy::Get()->Start();

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