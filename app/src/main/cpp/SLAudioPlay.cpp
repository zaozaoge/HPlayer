//
// Created by 胡章孝 on 2019/5/14.
//

#include "SLAudioPlay.h"
#include "XLog.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <libavcodec/avcodec.h>


static SLObjectItf engineSL = nullptr;
static SLEngineItf eng = nullptr;
static SLObjectItf mix = nullptr;
static SLObjectItf player = nullptr;
static SLPlayItf iplayer = nullptr;
static SLAndroidSimpleBufferQueueItf pcmQue = nullptr;

SLAudioPlay::SLAudioPlay() {
    buf = new unsigned char[1024 * 1024];
}

SLAudioPlay::~SLAudioPlay() {
    delete buf;
    buf = nullptr;
}

static SLEngineItf CreateSL() {
    SLresult re;
    SLEngineItf en;
    re = slCreateEngine(&engineSL, 0, 0, 0, 0, 0);
    if (re != SL_RESULT_SUCCESS)
        return nullptr;
    re = (*engineSL)->Realize(engineSL, SL_BOOLEAN_FALSE);
    if (re != SL_RESULT_SUCCESS) {
        return nullptr;
    }
    re = (*engineSL)->GetInterface(engineSL, SL_IID_ENGINE, &en);
    if (re != SL_RESULT_SUCCESS) {
        return nullptr;
    }
    return en;
}


static void PcmCall(SLAndroidSimpleBufferQueueItf bf, void *context) {
    auto *audioPlay = (SLAudioPlay *) context;
    if (!audioPlay) {
        XLoge("PcmCall failed context is null")
        return;
    }
    audioPlay->PlayCall((void *) bf);
}


void SLAudioPlay::PlayCall(void *bufq) {
    if (!bufq)return;;
    auto bf = (SLAndroidSimpleBufferQueueItf) bufq;
    XData d = GetData();
    if (d.size <= 0) {
        XLogi("GetData size is 0");
        return;
    }
    if (!buf)
        return;
    memcpy(buf, d.data, d.size);
    (*bf)->Enqueue(bf, buf, d.size);
    d.Drop();
}

bool SLAudioPlay::StartPlay(XParameter out) {
    //1、创建引擎
    eng = CreateSL();
    if (!eng) {
        XLogi("CreateSl failed")
        return false;
    }
    XLogi("CreateSl success")

    //2、创建混音器
    SLresult re = 0;
    re = (*eng)->CreateOutputMix(eng, &mix, 0, 0, 0);
    if (re != SL_RESULT_SUCCESS) {
        XLogi("CreateOutputMix failed");
        return false;
    }
    XLogi("CreateOutputMix success");
    re = (*mix)->Realize(mix, SL_BOOLEAN_FALSE);

    if (re != SL_RESULT_SUCCESS) {
        XLogi("mix Realize failed");
        return false;
    }
    XLogi("mix Realize success");
    SLDataLocator_OutputMix outputMix = {SL_DATALOCATOR_OUTPUTMIX, mix};
    SLDataSink audioSink = {&outputMix, 0};

    //3、配置音频信息
    //缓冲队列
    SLDataLocator_AndroidSimpleBufferQueue queue = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 10};
    //音频格式
    SLDataFormat_PCM pcm = {
            SL_DATAFORMAT_PCM,
            (SLuint32) out.channels,//声道数
            (SLuint32) out.sample_rate * 1000,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,
            SL_BYTEORDER_LITTLEENDIAN //字节序，小端
    };

    SLDataSource ds = {&queue, &pcm};

    //创建播放器
    const SLInterfaceID ids[] = {SL_IID_BUFFERQUEUE};
    const SLboolean req[] = {SL_BOOLEAN_TRUE};
    re = (*eng)->CreateAudioPlayer(eng, &player, &ds, &audioSink,
                                   sizeof(ids) / sizeof(SLInterfaceID), ids, req);
    if (re != SL_RESULT_SUCCESS) {
        XLogi("CreateAudioPlayer failed");
        return false;
    }
    XLogi("CreateAudioPlayer success");
    (*player)->Realize(player, SL_BOOLEAN_FALSE);
    //获取player接口
    re = (*player)->GetInterface(player, SL_IID_PLAY, &iplayer);
    if (re != SL_RESULT_SUCCESS) {
        XLogi("GetInterface SL_IID_PLAY failed");
        return false;
    }
    XLogi("GetInterface SL_IID_PLAY success");
    re = (*player)->GetInterface(player, SL_IID_BUFFERQUEUE, &pcmQue);

    if (re != SL_RESULT_SUCCESS) {
        XLogi("GetInterface SL_IID_BUFFERQUEUE failed");
        return false;
    }
    XLogi("GetInterface SL_IID_BUFFERQUEUE success");

    //设置回调函数，播放队列空调用
    (*pcmQue)->RegisterCallback(pcmQue, PcmCall, this);

    //设置为播放状态
    (*iplayer)->SetPlayState(iplayer, SL_PLAYSTATE_PLAYING);

    //启动队列回调
    (*pcmQue)->Enqueue(pcmQue, "", 1);
    XLogi("SLAudioPlay::StartPlay success");

    return true;
}
