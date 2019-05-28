//
// Created by 胡章孝 on 2019/4/13.
//

#ifndef ZPLAYER_IDEMUX_H
#define ZPLAYER_IDEMUX_H

#include "XData.h"
#include "XThread.h"
#include "IObserver.h"
#include "XParameter.h"

//解封装接口
class IDemux : public IObserver {
public:
    //打开文件或者流媒体 rtmp http rtsp
    virtual bool Open(const char *url) = 0;
    //
    virtual bool Seek(double pos) = 0;
    virtual void Close() = 0;

    //获取视频参数
    virtual XParameter GetVideoParams() = 0;

    //获取音频参数
    virtual XParameter GetAudioParams() = 0;

    //读取一帧数据，数据由调用者清理
    virtual XData Read() = 0;

    //总时长（毫秒）
    int totalMs = 0;
protected:
    void Main() override;
};


#endif //ZPLAYER_IDEMUX_H
