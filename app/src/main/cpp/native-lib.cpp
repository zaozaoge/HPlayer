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
#include "IAudioPlay.h"
#include "SLAudioPlay.h"
#include "IPlayer.h"
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

    //XSleep(3000);
    //de->Stop();
    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *res) {
    FFDecode::InitHard(vm);

    IDemux *de = new FFDemux();
    //de->Open("/sdcard/tencent/QQfile_recv/v1080.mp4");
    //打开视频解码器
    IDecode *vDecode = new FFDecode();
    //vDecode->Open(de->GetVideoParams(), true);
    //打开音频解码器
    IDecode *aDecode = new FFDecode();
    //aDecode->Open(de->GetAudioParams());
    //添加观察者
    de->AddObs(vDecode);
    de->AddObs(aDecode);

    videoView = new GLVideoView();
    vDecode->AddObs(videoView);


    IResample *resample = new FFResample();
    XParameter outParams = de->GetAudioParams();

    //resample->Open(de->GetAudioParams(), outParams);
    aDecode->AddObs(resample);

    IAudioPlay *audioPlay = new SLAudioPlay();
    // audioPlay->StartPlay(outParams);
    resample->AddObs(audioPlay);

    //de->Start();
    // vDecode->Start();
    // aDecode->Start();

    IPlayer::Get()->demux = de;
    IPlayer::Get()->audioDecode = aDecode;
    IPlayer::Get()->videoDecode = vDecode;
    IPlayer::Get()->resample = resample;
    IPlayer::Get()->audioPlay = audioPlay;
    IPlayer::Get()->videoView = videoView;
    IPlayer::Get()->Open("/sdcard/tencent/QQfile_recv/v1080.mp4");
    IPlayer::Get()->Start();

    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_zaozao_hplayer_XPlay_initView(JNIEnv *env, jobject instance, jobject surface) {

    ANativeWindow *nativeWindow = ANativeWindow_fromSurface(env, surface);
    IPlayer::Get()->InitView(nativeWindow);

}