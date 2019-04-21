//
// Created by 胡章孝 on 2019/4/21.
//

#ifndef ZPLAYER_IDEOCDE_H
#define ZPLAYER_IDEOCDE_H

#include "XParameter.h"
#include "IObserver.h"

//解码接口，支持硬解码
class IDecode : public IObserver {
public:

    //打开解码器
    virtual bool Open(XParameter xParameter) = 0;

    //future模型,发送数据到线程解码
    virtual bool SendPacket(XData pkt) = 0;

    //从线程中获取解码结果
    virtual XData ReceiveFrame() = 0;
};


#endif //ZPLAYER_IDEOCDE_H
