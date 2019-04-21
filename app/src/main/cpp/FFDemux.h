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
    virtual bool Open(const char *url);

    //获取视频参数
    virtual XParameter GetVideoParams();

    //获取音频参数
    virtual XParameter GetAudioParams();

    //读取一帧数据，数据由调用者清理
    virtual XData Read();

    FFDemux();

private:
    AVFormatContext *ic = 0;
    int audioStreamIndex = 1;
    int videoSteamIndex = 0;
};


#endif ZPLAYER_FFDEMUX_H
