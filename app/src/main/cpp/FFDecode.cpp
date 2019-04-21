//
// Created by 胡章孝 on 2019/4/21.
//

extern "C" {
#include <libavcodec/avcodec.h>
}

#include "FFDecode.h"
#include "XLog.h"

bool FFDecode::Open(XParameter xParameter) {

    if (!xParameter.parameters)
        return false;
    AVCodecParameters *parameters = xParameter.parameters;
    //1、查找解码器
    AVCodec *avCodec = avcodec_find_decoder(parameters->codec_id);
    if (!avCodec) {
        XLoge("avcodec_find_decoder %d failed", parameters->codec_id);
        return false;
    }
    XLogi("avcodec_find_decoder %d success", parameters->codec_id);
    //2、创建解码上下文，并复制参数
    avCodecContext = avcodec_alloc_context3(avCodec);
    avcodec_parameters_to_context(avCodecContext, parameters);

    //3、打开解码器
    int result = avcodec_open2(avCodecContext, 0, 0);
    if (result != 0) {
        char buf[1024] = {0};
        av_strerror(result, buf, sizeof(buf) - 1);
        XLoge("%s", buf);
        return false;
    }
    XLogi("avcodec_open2 success");
    return true;
}
