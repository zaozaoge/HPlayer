//
// Created by 胡章孝 on 2019/5/13.
//

#ifndef ZPLAYER_FFRESAMPLE_H
#define ZPLAYER_FFRESAMPLE_H


#include "IResample.h"

struct SwrContext;

class FFResample : public IResample {

public:

    bool Open(XParameter in, XParameter out) override;

    XData Resample(XData inData) override;

protected:
    SwrContext *actx = 0;
};


#endif //ZPLAYER_FFRESAMPLE_H
