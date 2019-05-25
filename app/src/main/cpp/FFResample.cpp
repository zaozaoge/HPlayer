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
    Close();
    //音频重采样上下文初始化
    mutex.lock();
    actx = swr_alloc();
    actx = swr_alloc_set_opts(actx,
                              av_get_default_channel_layout(out.channels),
                              AV_SAMPLE_FMT_S16,
                              out.sample_rate,
                              av_get_default_channel_layout(in.parameters->channels),
                              (AVSampleFormat) in.parameters->format,
                              in.parameters->sample_rate,
                              0,
                              nullptr);

    int re = swr_init(actx);
    if (re != 0) {
        XLogi("swr_init failed");
        mutex.unlock();
        return false;
    }

    XLogi("swr_init success");

    outChannels = in.parameters->channels;
    outFormat = AV_SAMPLE_FMT_S16;
    mutex.unlock();
    return true;

}

XData FFResample::Resample(XData inData) {

    if (!inData.data || inData.size <= 0)
        return {};
    if (!actx) {
        mutex.lock();
        return {};
    }
    //输出空间的分配
    XData out;
    auto *frame = reinterpret_cast<AVFrame *>(inData.data);
    //通道数*单通道样本数*样本字节大小
    int outsize = outChannels * frame->nb_samples * av_get_bytes_per_sample(
            static_cast<AVSampleFormat>(outFormat));
    if (outsize <= 0){
        mutex.unlock();
        return {};
    }
    out.Alloc(outsize);
    uint8_t *outArray[2] = {nullptr};
    outArray[0] = out.data;
    int len = swr_convert(actx, outArray, frame->nb_samples,
                          (const uint8_t **) frame->data, frame->nb_samples);
    if (len <= 0) {
        out.Drop();
        mutex.unlock();
        return {};
    }
    out.pts = inData.pts;
    //XLogi("swr_convert success %d", len);
    mutex.unlock();
    return out;
}

void FFResample::Close() {
    mutex.lock();
    if (actx) {
        swr_free(&actx);
    }
    mutex.unlock();
}
