//
// Created by 胡章孝 on 2019/4/21.
//

#ifndef ZPLAYER_IDEOCDE_H
#define ZPLAYER_IDEOCDE_H

#include "XParameter.h"

//解码接口，支持硬解码
class IDeocde {
public:

    //打开解码器
    virtual bool Open(XParameter xParameter) = 0;
};


#endif //ZPLAYER_IDEOCDE_H
