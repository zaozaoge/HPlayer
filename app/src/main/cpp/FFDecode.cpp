//
// Created by 胡章孝 on 2019/4/21.
//

#include "FFDecode.h"

bool FFDecode::Open(XParameter xParameter) {

    if (!xParameter.parameters)
        return false;
    AVCodecParameters *parameters = xParameter.parameters;

    return true;
}
