#include <jni.h>
#include <string>

#include "FFDemux.h"
#include "XLog.h"
#include "IDecode.h"
#include "FFDecode.h"

class TestObs : public IObserver {
public:
    void Update(XData data) override {
        IObserver::Update(data);
       // XLogi("TestObs Update data size is %d", data.size);
    }
};

extern "C" JNIEXPORT jstring JNICALL
Java_com_zaozao_hplayer_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    IDemux *de = new FFDemux();
    auto *obs = new TestObs();
    de->AddObs(obs);
    de->Open("/sdcard/DCIM/Camera/VID_20180215_142837.mp4");
    IDecode *vDecode = new FFDecode();
    vDecode->Open(de->GetVideoParams());
    de->Start();
    XSleep(3000);
    de->Stop();
    return env->NewStringUTF(hello.c_str());
}
