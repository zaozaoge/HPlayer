//
// Created by 胡章孝 on 2019/5/17.
//

#ifndef ZPLAYER_IPLAYERBUILDER_H
#define ZPLAYER_IPLAYERBUILDER_H

#include "IPlayer.h"

class IPlayerBuilder {
public:

    virtual IPlayer *BuilderPlayer(unsigned char index = 0);

protected:
    virtual IDemux *CreateDemux() = 0;

    virtual IDecode *CreateDecode() = 0;

    virtual IResample *CreateResample() = 0;

    virtual IVideoView *CreateVideoView() = 0;

    virtual IAudioPlay *CreateAudioPlayer() = 0;

    virtual IPlayer *CreatePlayer(unsigned char index) = 0;
};


#endif //ZPLAYER_IPLAYERBUILDER_H
