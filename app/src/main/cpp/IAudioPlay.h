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

    //获取缓冲数据，如没有则阻塞
    virtual XData GetData();

    virtual bool StartPlay(XParameter out = XParameter()) = 0;

    virtual void Close() = 0;

    virtual void Clear();
    //最大缓冲
    int maxFrames = 100;

    int pts = 0;
protected:
    std::list<XData> frames;
    std::mutex framesMutex;
};


#endif //ZPLAYER_IAUDIOPLAY_H
