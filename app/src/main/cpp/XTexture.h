//
// Created by 胡章孝 on 2019/5/11.
//

#ifndef ZPLAYER_XTEXTURE_H
#define ZPLAYER_XTEXTURE_H

enum XTextureType {
    XTEXTURE_YUV420P = 0, // y4 u1 v1
    XTEXTURE_NV21 = 26,   // y4 vu1
    XTEXTURE_NV12 = 25   // y4 uv1
};

class XTexture {
public:
    static XTexture *Create();

    virtual bool Init(void *win, XTextureType type = XTEXTURE_YUV420P) = 0;

    virtual void Draw(unsigned char *data[], int width, int height) = 0;

    virtual void Drop() = 0;

    virtual ~XTexture() = default;

protected:
    XTexture() = default;
};


#endif //ZPLAYER_XTEXTURE_H
