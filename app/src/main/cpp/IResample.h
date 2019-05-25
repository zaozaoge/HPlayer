//
// Created by 胡章孝 on 2019/5/13.
//

#ifndef ZPLAYER_IRESAMPLE_H
#define ZPLAYER_IRESAMPLE_H


#include "IObserver.h"
#include "XParameter.h"

class IResample : public IObserver {
public:
    virtual bool Open(XParameter in, XParameter out = {}) = 0;

    virtual void Close() = 0;

    virtual XData Resample(XData inData) = 0;

    void Update(XData xData) override;

    int outChannels = 2;

    int outFormat = 1;
};


#endif //ZPLAYER_IRESAMPLE_H
