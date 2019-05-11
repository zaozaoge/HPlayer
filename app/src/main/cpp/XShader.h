//
// Created by 胡章孝 on 2019/5/11.
//

#ifndef ZPLAYER_XSHADER_H
#define ZPLAYER_XSHADER_H


class XShader {
public:
    virtual bool Init();

protected:
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
};


#endif //ZPLAYER_XSHADER_H
