//
// Created by 胡章孝 on 2019/5/11.
//

#include "XEGL.h"

class CXEGL : public XEGL {

public:
    virtual bool Init(void *win) {
        return true;
    }
};

XEGL *XEGL::Get() {
    static CXEGL egl;
    return &egl;
}


