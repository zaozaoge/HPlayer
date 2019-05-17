//
// Created by 胡章孝 on 2019/5/17.
//

#ifndef ZPLAYER_FFPLAYERBUILDER_H
#define ZPLAYER_FFPLAYERBUILDER_H


#include "IPlayerBuilder.h"

class FFPlayerBuilder : public IPlayerBuilder {

public:
    static FFPlayerBuilder *Get() {
        static FFPlayerBuilder ff;
        return &ff;
    }

    static void InitHard(void *vm);


protected:

    FFPlayerBuilder() = default;

    IDemux *CreateDemux() override;

    IDecode *CreateDecode() override;

    IResample *CreateResample() override;

    IVideoView *CreateVideoView() override;

    IAudioPlay *CreateAudioPlayer() override;

    IPlayer *CreatePlayer(unsigned char index) override;
};


#endif //ZPLAYER_FFPLAYERBUILDER_H
