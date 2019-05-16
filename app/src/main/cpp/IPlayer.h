//
// Created by 胡章孝 on 2019/5/16.
//

#ifndef ZPLAYER_IPLAYER_H
#define ZPLAYER_IPLAYER_H


#include "XThread.h"


class IDemux;

class IDecode;

class IResample;

class IAudioPlay;

class IVideoView;

class IPlayer : public XThread {
public:
    static IPlayer *Get(unsigned char index = 0);

    virtual bool Open(const char *path);
    virtual bool Start();
    //是否视频硬解码
    bool isHardDecode = true;
    IDemux *demux = nullptr;
    IDecode *audioDecode = nullptr;
    IDecode *videoDecode = nullptr;
    IResample *resample = nullptr;
    IAudioPlay *audioPlay = nullptr;
    IVideoView *videoView = nullptr;
protected:
    IPlayer(){

    }

};


#endif //ZPLAYER_IPLAYER_H
