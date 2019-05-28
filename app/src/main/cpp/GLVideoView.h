//
// Created by 胡章孝 on 2019/5/11.
//

#ifndef ZPLAYER_GLVIDEOVIEW_H
#define ZPLAYER_GLVIDEOVIEW_H


#include "XData.h"
#include "IVideoView.h"

class XTexture;

class GLVideoView : public IVideoView {
public:
    void SetRender(void *win) override;

    void Render(XData data) override;

    void Close() override;

    bool IsReady() override;


protected:
    void *view = nullptr;
    XTexture *txt = nullptr;
    std::mutex mutex;
};


#endif //ZPLAYER_GLVIDEOVIEW_H
