//
// Created by 胡章孝 on 2019/4/21.
//

#ifndef ZPLAYER_FFDECODE_H
#define ZPLAYER_FFDECODE_H


#include "XParameter.h"
#include "IDeocde.h"

class FFDecode :public IDeocde{
    virtual bool Open(XParameter xParameter);

};


#endif //ZPLAYER_FFDECODE_H
