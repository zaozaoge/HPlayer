//
// Created by 胡章孝 on 2019/5/11.
//

#ifndef ZPLAYER_IVIDEOVIEW_H
#define ZPLAYER_IVIDEOVIEW_H


#include "XData.h"
#include "IObserver.h"

class IVideoView : public IObserver {
public:
    virtual void SetRender(void *win) = 0;

    virtual void Render(XData data) = 0;

    void Update(XData xData) override;

    virtual void Close() = 0;

    //是否已经开始渲染画面
    virtual bool IsReady() = 0;


    bool isReady = false;
};


#endif //ZPLAYER_IVIDEOVIEW_H
