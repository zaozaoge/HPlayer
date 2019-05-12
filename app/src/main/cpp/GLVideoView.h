//
// Created by 胡章孝 on 2019/5/11.
//

#ifndef ZPLAYER_GLVIDEOVIEW_H
#define ZPLAYER_GLVIDEOVIEW_H


#include "XData.h"
class XTexture;
class GLVideoView {
public:
    virtual void SetRender(void *win);
    virtual void Render(XData data);

protected:
    void *view = 0;
    XTexture *txt = 0;

};


#endif //ZPLAYER_GLVIDEOVIEW_H
