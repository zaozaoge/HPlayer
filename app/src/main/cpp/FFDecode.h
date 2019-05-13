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
    bool Open(XParameter xParameter) override;

    //future模型,发送数据到线程解码
    bool SendPacket(XData pkt) override;

    //从线程中获取解码结果，再次调用会复用上次空间，线程不安全
    XData ReceiveFrame() override;

protected:
    AVCodecContext *avCodecContext;
    AVFrame *frame = 0;

};


#endif //ZPLAYER_FFDECODE_H
