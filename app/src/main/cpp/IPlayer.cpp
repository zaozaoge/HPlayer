//
// Created by 胡章孝 on 2019/5/16.
//

#include "IPlayer.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IResample.h"
#include "IAudioPlay.h"
#include "IVideoView.h"
#include "XLog.h"

IPlayer *IPlayer::Get(unsigned char index) {
    static IPlayer p[256];

    return &p[index];
}

bool IPlayer::Open(const char *path) {
    mutex.lock();
    //解封装
    if (!demux || !demux->Open(path)) {
        XLoge("demux open %s failed", path);
        mutex.unlock();
        return false;
    }

    //解码，解码可能不需要，如果解封之后就是原始数据
    if (!videoDecode || !videoDecode->Open(demux->GetVideoParams(), isHardDecode)) {
        XLoge("videoDecode open %s failed", path);
        // return false;
    }

    if (!audioDecode || !audioDecode->Open(demux->GetAudioParams())) {
        XLoge("audioDecode open %s failed", path);
        // return false;
    }
    //重采样，重采样有可能不需要，解码或者解封之后可能是直接能播放的数据
    if (out.sample_rate <= 0)
        out = demux->GetAudioParams();
    if (!resample || !resample->Open(demux->GetAudioParams(), out)) {
        XLoge("resample open %s failed", path);
    }
    mutex.unlock();
    return true;
}

bool IPlayer::Start() {

    mutex.lock();
    if (!demux || !demux->Start()) {
        XLoge("demux start failed");
        mutex.unlock();
        return false;
    }

    if (audioDecode) {
        audioDecode->Start();
    }
    if (audioPlay) {
        audioPlay->StartPlay(out);
    }

    if (videoDecode) {
        videoDecode->Start();
    }
    XThread::Start();
    mutex.unlock();
    return true;
}

void IPlayer::InitView(void *win) {
    if (videoView) {
        videoView->SetRender(win);
    }
}

void IPlayer::Main() {

    while (!isExit) {
        mutex.lock();
        if (!audioPlay || !videoDecode) {
            //如果音频播放或者视频解码器有一个不存在，则不用做同步
            mutex.unlock();
            XSleep(2);
            continue;
        }
        //同步
        //获取音频的pts告诉视频
        int apts = audioPlay->pts;
        videoDecode->synPTS = apts;
        mutex.unlock();
        XSleep(2);
    }
}






