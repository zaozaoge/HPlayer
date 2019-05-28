//
// Created by 胡章孝 on 2019/4/13.
//

#ifndef ZPLAYER_FFDEMUX_H
#define ZPLAYER_FFDEMUX_H


#include "XData.h"
#include "IDemux.h"

struct AVFormatContext;

class FFDemux : public IDemux {
public:
    //打开文件或者流媒体 rtmp http rtsp
    bool Open(const char *url) override;

    void Close() override;

    //获取视频参数
    XParameter GetVideoParams() override;

    bool Seek(double pos) override;

    //获取音频参数
    XParameter GetAudioParams() override;

    //读取一帧数据，数据由调用者清理
    XData Read() override;

    FFDemux();

private:
    AVFormatContext *ic = nullptr;
    std::mutex mutex;
    int audioStreamIndex = 1;
    int videoSteamIndex = 0;
};


#endif ZPLAYER_FFDEMUX_H
