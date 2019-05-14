#include <jni.h>
#include <string>

#include "FFDemux.h"
#include "XLog.h"
#include "IDecode.h"
#include "FFDecode.h"
#include "XEGL.h"
#include "XShader.h"
#include "IVideoView.h"
#include "GLVideoView.h"
#include "FFResample.h"
#include <android/native_window_jni.h>

class TestObs : public IObserver {
public:
    void Update(XData data) override {
        IObserver::Update(data);
        // XLogi("TestObs Update data size is %d", data.size);
    }
};

IVideoView *videoView = nullptr;

extern "C" JNIEXPORT jstring JNICALL
Java_com_zaozao_hplayer_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    IDemux *de = new FFDemux();
    auto *obs = new TestObs();
    de->Open("/sdcard/DCIM/Camera/VID_20180215_142837.mp4");
    //打开视频解码器
    IDecode *vDecode = new FFDecode();
    vDecode->Open(de->GetVideoParams());
    //打开音频解码器
    IDecode *aDecode = new FFDecode();
    aDecode->Open(de->GetAudioParams());
    //添加观察者
    de->AddObs(vDecode);
    de->AddObs(aDecode);

    videoView = new GLVideoView();
    vDecode->AddObs(videoView);


    IResample *resample = new FFResample();
    resample->Open(de->GetAudioParams());
    aDecode->AddObs(resample);
    de->Start();
    vDecode->Start();
    aDecode->Start();
    //XSleep(3000);
    //de->Stop();
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_zaozao_hplayer_XPlay_initView(JNIEnv *env, jobject instance, jobject surface) {

    ANativeWindow *nativeWindow = ANativeWindow_fromSurface(env, surface);
//    XEGL::Get()->Init(nativeWindow);
//    XShader xShader;
//    xShader.Init();
    videoView->SetRender(nativeWindow);
}