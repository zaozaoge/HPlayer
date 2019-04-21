//
// Created by 胡章孝 on 2019/4/21.
//

#ifndef ZPLAYER_FFDECODE_H
#define ZPLAYER_FFDECODE_H


#include "XParameter.h"
#include "IDecode.h"

struct AVCodecContext;
struct AVFrame;
class FFDecode : public IDecode {
public:
    virtual bool Open(XParameter xParameter);

    //future模型,发送数据到线程解码
    virtual bool SendPacket(XData pkt);

    //从线程中获取解码结果
    virtual XData ReceiveFrame();

protected:
    AVCodecContext *avCodecContext;
    AVFrame *frame = 0;

};


#endif //ZPLAYER_FFDECODE_H
