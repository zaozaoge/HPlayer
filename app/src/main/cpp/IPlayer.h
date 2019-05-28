//
// Created by 胡章孝 on 2019/5/16.
//

#ifndef ZPLAYER_IPLAYER_H
#define ZPLAYER_IPLAYER_H


#include <mutex>
#include "XThread.h"
#include "XParameter.h"


class IDemux;

class IDecode;

class IResample;

class IAudioPlay;

class IVideoView;

class IPlayer : public XThread {
public:
    static IPlayer *Get(unsigned char index = 0);

    virtual bool Open(const char *path);

    virtual void Close();

    bool Start() override;

    virtual void InitView(void *win);

    void SetPause(bool isPause) override;


    //获取当前的播放信息
    virtual double PlayPos();
    virtual bool Seek(double pos);

    virtual bool IsReady();

    //是否视频硬解码
    bool isHardDecode = true;
    //音频输出参数配置
    XParameter out;
    IDemux *demux = nullptr;
    IDecode *audioDecode = nullptr;
    IDecode *videoDecode = nullptr;
    IResample *resample = nullptr;
    IAudioPlay *audioPlay = nullptr;
    IVideoView *videoView = nullptr;
protected:
    void Main() override;

    std::mutex mutex;

    IPlayer() = default;

};


#endif //ZPLAYER_IPLAYER_H
