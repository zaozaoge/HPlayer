//
// Created by 胡章孝 on 2019/5/14.
//

#ifndef ZPLAYER_IAUDIOPLAY_H
#define ZPLAYER_IAUDIOPLAY_H


#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay: public IObserver {
public:
    virtual void Update(XData xData);
    virtual bool StartPlay(XParameter out) = 0;
};


#endif //ZPLAYER_IAUDIOPLAY_H
