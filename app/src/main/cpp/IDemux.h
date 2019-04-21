//
// Created by 胡章孝 on 2019/4/13.
//

#ifndef ZPLAYER_IDEMUX_H
#define ZPLAYER_IDEMUX_H

#include "XData.h"

//解封装接口
class IDemux {
public:
    //打开文件或者流媒体 rtmp http rtsp
    virtual bool Open(const char *url) = 0;

    //读取一帧数据，数据由调用者清理
    virtual XData Read() = 0;

    //总时长（毫秒）
    int totalMs = 0;
};


#endif //ZPLAYER_IDEMUX_H
