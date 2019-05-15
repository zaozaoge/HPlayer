//
// Created by 胡章孝 on 2019/5/14.
//

#ifndef ZPLAYER_SLAUDIOPLAY_H
#define ZPLAYER_SLAUDIOPLAY_H


#include "IAudioPlay.h"

class SLAudioPlay : public IAudioPlay {
public:
    bool StartPlay(XParameter out) override;

    void PlayCall(void *bufq);

    SLAudioPlay();

    virtual ~SLAudioPlay();

protected:
    unsigned char *buf = nullptr;
};


#endif //ZPLAYER_SLAUDIOPLAY_H
