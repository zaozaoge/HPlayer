//
// Created by 胡章孝 on 2019/5/11.
//

#ifndef ZPLAYER_XSHADER_H
#define ZPLAYER_XSHADER_H

#include <mutex>

enum XShaderType {
    XSHADER_YUV420P = 0, // y4 u1 v1  软解码
    XSHADER_NV21 = 26,   // y4 vu1
    XSHADER_NV12 = 25   // y4 uv1
};

class XShader {
public:
    virtual bool Init(XShaderType type = XSHADER_YUV420P);

    virtual void Close();

    //获取材质并映射到内存
    virtual void
    GetTexture(unsigned int index, int width, int height, unsigned char *buf, bool isAlpha = false);

    virtual void Draw();

protected:
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = {0};
    std::mutex mutex;
};


#endif //ZPLAYER_XSHADER_H
