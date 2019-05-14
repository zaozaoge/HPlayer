//
// Created by 胡章孝 on 2019/5/13.
//

#ifndef ZPLAYER_FFRESAMPLE_H
#define ZPLAYER_FFRESAMPLE_H


#include "IResample.h"

struct SwrContext;
class FFResample : public IResample{

public:
    virtual bool Open(XParameter in, XParameter out = XParameter());

protected:
    SwrContext *actx = 0;
};


#endif //ZPLAYER_FFRESAMPLE_H
