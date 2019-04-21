//
// Created by 胡章孝 on 2019/4/21.
//

#ifndef ZPLAYER_FFDECODE_H
#define ZPLAYER_FFDECODE_H


#include "XParameter.h"
#include "IDecode.h"

struct AVCodecContext;

class FFDecode : public IDecode {
public:
    virtual bool Open(XParameter xParameter);

protected:
    AVCodecContext *avCodecContext;
};


#endif //ZPLAYER_FFDECODE_H
