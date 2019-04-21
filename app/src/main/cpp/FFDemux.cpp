//
// Created by 胡章孝 on 2019/4/13.
//

#include "FFDemux.h"
#include "XLog.h"

extern "C" {
#include "include/libavformat/avformat.h"
#include "include/libavcodec/avcodec.h"
#include "include/libavutil/error.h"
#include "include/libavutil/avutil.h"
}

//打开文件或者流媒体 rtmp http rtsp
bool FFDemux::Open(const char *url) {
    XLogi("open file %s begin", url);
    int result = avformat_open_input(&ic, url, 0, 0);
    if (result != 0) {
        char buf[1024] = {0};
        av_strerror(result, buf, sizeof(buf));
        XLogi("FFDemux open %s failed!", url);
        return false;
    }
    XLogi("FFDemux open %s success!", url);
    //读取文件信息
    result = avformat_find_stream_info(ic, 0);
    if (result != 0) {
        char buf[1024] = {0};
        av_strerror(result, buf, sizeof(buf));
        XLogi("avformat_find_stream_info %s failed!", url);
        return false;
    }
    this->totalMs = static_cast<int>(ic->duration / (AV_TIME_BASE / 1000));
    XLogi("total ms = %d", totalMs);

    return true;
}

//读取一帧数据，数据由调用者清理
XData FFDemux::Read() {
    if (!ic)
        return {};
    XData d;
    AVPacket *pkt = av_packet_alloc();
    int result = av_read_frame(ic, pkt);
    if (result != 0) {
        XLogi("av_read_frame  failed!");
        //读取失败，释放内存
        av_packet_free(&pkt);
        return {};
    }
    XLogi("packet size is %d ,pts is %lld", pkt->size, pkt->pts);
    d.data = reinterpret_cast<unsigned char *>(pkt);
    d.size = pkt->size;
    return d;
}

FFDemux::FFDemux() {
    static bool isFirst = true;
    if (isFirst) {
        isFirst = false;
        //注册所有解封装器
        av_register_all();
        //注册所有解码器
        avcodec_register_all();
        //初始化网络
        avformat_network_init();
        XLogi("register ffmpeg !");

    }
}