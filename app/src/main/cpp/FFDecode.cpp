//
// Created by 胡章孝 on 2019/4/21.
//

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavcodec/jni.h>
}

#include "FFDecode.h"
#include "XLog.h"


void FFDecode::InitHard(void *vm) {
    av_jni_set_java_vm(vm, nullptr);
}

bool FFDecode::Open(XParameter xParameter, bool isHard) {

    if (!xParameter.parameters)
        return false;
    AVCodecParameters *parameters = xParameter.parameters;
    //1、查找解码器
    AVCodec *avCodec = avcodec_find_decoder(parameters->codec_id);
    if (isHard) {
        avCodec = avcodec_find_decoder_by_name("h264_mediacodec");
    }
    if (!avCodec) {
        XLoge("avcodec_find_decoder %d failed %d", parameters->codec_id, isHard);
        return false;
    }
    XLogi("avcodec_find_decoder %d success %d", parameters->codec_id, isHard);
    //2、创建解码上下文，并复制参数
    avCodecContext = avcodec_alloc_context3(avCodec);
    avcodec_parameters_to_context(avCodecContext, parameters);

    //3、打开解码器
    avCodecContext->thread_count = 8;//开启多线程解码
    int result = avcodec_open2(avCodecContext, 0, 0);
    if (result != 0) {
        char buf[1024] = {0};
        av_strerror(result, buf, sizeof(buf) - 1);
        XLoge("%s", buf);
        return false;
    }
    this->isAudio = avCodecContext->codec_type == AVMEDIA_TYPE_AUDIO;
    XLogi("avcodec_open2 success");
    return true;
}

//future模型,发送数据到线程解码
bool FFDecode::SendPacket(XData pkt) {
    if (pkt.size <= 0 || !pkt.data)return false;
    if (!avCodecContext) {
        return false;
    }
    int result = avcodec_send_packet(avCodecContext, reinterpret_cast<const AVPacket *>(pkt.data));
    return result == 0;
}

//从线程中获取解码结果
XData FFDecode::ReceiveFrame() {
    if (!avCodecContext) {
        return {};
    }
    if (!frame) {
        frame = av_frame_alloc();
    }
    int result = avcodec_receive_frame(avCodecContext, frame);
    if (result != 0) {
        return {};
    }
    XData data;
    data.data = (unsigned char *) frame;
    if (avCodecContext->codec_type == AVMEDIA_TYPE_VIDEO) {
        data.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2]) * frame->height;
        data.width = frame->width;
        data.height = frame->height;
    } else {
        //样本字节数*单通道样本数*通道数
        data.size = av_get_bytes_per_sample(AVSampleFormat(frame->format)) * frame->nb_samples * 2;
    }
    data.format = frame->format;
    memcpy(data.datas, frame->data, sizeof(data.datas));
    return data;

}
