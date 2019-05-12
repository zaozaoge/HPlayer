//
// Created by 胡章孝 on 2019/5/11.
//

#ifndef ZPLAYER_IVIDEOVIEW_H
#define ZPLAYER_IVIDEOVIEW_H


#include "XData.h"

class IVideoView {
public:
    virtual void SetRender(void *win) = 0;
    virtual void Render(XData data) = 0;
    virtual void update(XData xData);
};


#endif //ZPLAYER_IVIDEOVIEW_H
