//
// Created by 胡章孝 on 2019/5/11.
//

#include "XTexture.h"
#include "XLog.h"
#include "XEGL.h"
#include "XShader.h"

class CXTexture : public XTexture {

public:
    XShader sh;

    virtual bool Init(void *win) {
        if (!win) {
            XLogi("Init XTexture failed")
            return false;
        }
        if (!XEGL::Get()->Init(win)) {
            XLogi("Init XEGL failed")
            return false;
        }
        sh.Init();
        return true;
    }

};

XTexture *XTexture::Create() {
    return new CXTexture();
}


