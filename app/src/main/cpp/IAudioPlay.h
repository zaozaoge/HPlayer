//
// Created by 胡章孝 on 2019/5/14.
//

#ifndef ZPLAYER_IAUDIOPLAY_H
#define ZPLAYER_IAUDIOPLAY_H


#include <list>
#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay : public IObserver {
public:

    //缓冲满后阻塞
    void Update(XData xData) override;

    virtual bool StartPlay(XParameter out) = 0;

    //最大缓冲
    int maxFrames = 100;
protected:
    std::list<XData> frames;
    std::mutex framesMutex;
};


#endif //ZPLAYER_IAUDIOPLAY_H
