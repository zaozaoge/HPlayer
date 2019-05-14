//
// Created by 胡章孝 on 2019/5/13.
//

extern "C"
{
#include <libswresample/swresample.h>
}

#include <libavcodec/avcodec.h>
#include "FFResample.h"
#include "XLog.h"

bool FFResample::Open(XParameter in, XParameter out) {
    //音频重采样上下文初始化
    actx = swr_alloc();
    actx = swr_alloc_set_opts(actx,
                              av_get_default_channel_layout(2),
                              AV_SAMPLE_FMT_S16,
                              in.parameters->sample_rate,
                              av_get_default_channel_layout(in.parameters->channels),
                              (AVSampleFormat) in.parameters->format,
                              in.parameters->sample_rate,
                              0,
                              nullptr);

    int re = swr_init(actx);
    if (re != 0) {
        XLogi("swr_init failed");
        return false;
    }

    XLogi("swr_init success");
    return true;

}