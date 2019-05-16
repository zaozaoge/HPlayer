//
// Created by 胡章孝 on 2019/5/16.
//

#include "IPlayer.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IResample.h"
#include "XLog.h"

IPlayer *IPlayer::Get(unsigned char index) {
    static IPlayer p[256];

    return &p[index];
}

bool IPlayer::Open(const char *path) {

    //解封装
    if (!demux || !demux->Open(path)) {
        XLoge("demux open %s failed", path);
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
    XParameter out = demux->GetAudioParams();
    if (!resample || !resample->Open(demux->GetAudioParams(), out)) {
        XLoge("resample open %s failed", path);
    }
    return true;
}

bool IPlayer::Start() {

}

