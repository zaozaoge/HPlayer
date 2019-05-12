//
// Created by 胡章孝 on 2019/5/11.
//

#ifndef ZPLAYER_XTEXTURE_H
#define ZPLAYER_XTEXTURE_H


class XTexture {
public:
    static XTexture *Create();
    virtual bool Init(void *win) = 0;
};


#endif //ZPLAYER_XTEXTURE_H
