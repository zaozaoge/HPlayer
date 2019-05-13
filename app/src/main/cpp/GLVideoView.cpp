//
// Created by 胡章孝 on 2019/5/11.
//

#include "GLVideoView.h"
#include "XTexture.h"
#include "XLog.h"

void GLVideoView::SetRender(void *win) {
    view = win;
}

void GLVideoView::Render(XData data) {
    if (!view)
        return;;

    if (!txt) {
        txt = XTexture::Create();
        txt->Init(view);
    }
    XLogi("start Render");
    txt->Draw(data.datas, data.width, data.height);
}
