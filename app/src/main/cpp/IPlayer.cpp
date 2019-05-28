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

void IPlayer::Close() {
    mutex.lock();
    //先关闭主体线程，再清理观察者
    //同步线程
    XThread::Stop();
    //解封装清理
    if (demux)
        demux->Stop();
    //解码清理
    if (videoDecode)
        videoDecode->Stop();
    if (audioDecode)
        audioDecode->Stop();
    //清理缓冲队列
    if (videoDecode)
        videoDecode->Clear();
    if (audioDecode)
        audioDecode->Clear();
    if (audioPlay)
        audioPlay->Clear();
    //清理资源
    if (audioPlay)
        audioPlay->Close();
    if (videoView)
        videoView->Close();
    if (audioDecode)
        audioDecode->Close();
    if (videoDecode)
        videoDecode->Close();
    if (demux)
        demux->Close();
    mutex.unlock();
}

bool IPlayer::Open(const char *path) {
    Close();
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
    out = demux->GetAudioParams();
    if (!resample || !resample->Open(demux->GetAudioParams(), out)) {
        XLoge("resample open %s failed", path);
    }
    mutex.unlock();
    return true;
}

bool IPlayer::Start() {

    mutex.lock();


    if (audioPlay) {
        XLoge("开始播放");
        audioPlay->StartPlay(out);
    }

    if (videoDecode) {
        XLoge("开始视频解码");
        videoDecode->Start();
    }
    if (audioDecode) {
        XLoge("开始音频解码");
        audioDecode->Start();
    }
    if (!demux || !demux->Start()) {
        XLoge("demux start failed");
        mutex.unlock();
        return false;
    }
    XLoge("开始音视频同步");

    XThread::Start();
    mutex.unlock();
    return true;
}

void IPlayer::InitView(void *win) {
    if (videoView) {
        videoView->Close();
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

double IPlayer::PlayPos() {
    double pos = 0.0;
    mutex.lock();
    int total = 0;
    if (demux) {
        total = demux->totalMs;
    }
    if (total > 0) {
        if (videoDecode) {
            pos = (double) videoDecode->pts / (double) total;
        }
    } else {
        mutex.unlock();
        return -1;
    }
    mutex.unlock();
    return pos;
}

bool IPlayer::IsReady() {
    if (videoView) {
        return videoView->IsReady();
    }
    return false;
}

bool IPlayer::Seek(double pos) {
    bool result = false;
    mutex.lock();
    if (demux) {
        result = demux->Seek(pos);
    }
    mutex.unlock();
    return result;
}

void IPlayer::SetPause(bool isPause) {
    mutex.lock();
    XThread::SetPause(isPause);
    if (demux) {
        demux->SetPause(isPause);
    }
    if (videoDecode) {
        videoDecode->SetPause(isPause);
    }
    if (audioDecode) {
        audioDecode->SetPause(isPause);
    }
    if (audioPlay) {
        audioPlay->SetPause(isPause);
    }
    mutex.unlock();
}








