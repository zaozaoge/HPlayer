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
    XTextureType type;

    bool Init(void *win, XTextureType type) override {
        this->type = type;
        if (!win) {
            XLogi("Init XTexture failed")
            return false;
        }
        if (!XEGL::Get()->Init(win)) {
            XLogi("Init XEGL failed")
            return false;
        }
        sh.Init((XShaderType)type);
        return true;
    }

    void Draw(unsigned char *data[], int width, int height) override {

        sh.GetTexture(0, width, height, data[0]); //Y
        if (type == XTEXTURE_YUV420P) {
            sh.GetTexture(1, width / 2, height / 2, data[1]); //U
            sh.GetTexture(2, width / 2, height / 2, data[2]); //V
        } else {
            sh.GetTexture(1, width / 2, height / 2, data[1], true); //uv
        }
        sh.Draw();
        XEGL::Get()->Draw();
    }

};

XTexture *XTexture::Create() {
    return new CXTexture();
}




