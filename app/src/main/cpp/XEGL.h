//
// Created by 胡章孝 on 2019/5/11.
//

#ifndef ZPLAYER_XEGL_H
#define ZPLAYER_XEGL_H


class XEGL {
public:
    virtual bool Init(void *win) = 0;
    virtual void Close() = 0;
    virtual void Draw() = 0;
    static XEGL *Get();

protected:
    XEGL(){}
};


#endif //ZPLAYER_XEGL_H
