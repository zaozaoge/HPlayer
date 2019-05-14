//
// Created by 胡章孝 on 2019/5/13.
//

#ifndef ZPLAYER_IRESAMPLE_H
#define ZPLAYER_IRESAMPLE_H


#include "IObserver.h"
#include "XParameter.h"

class IResample : public IObserver {
public:
    virtual bool Open(XParameter in, XParameter out = XParameter()) = 0;
};


#endif //ZPLAYER_IRESAMPLE_H
