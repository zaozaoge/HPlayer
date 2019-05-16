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
    GetVideoParams();
    GetAudioParams();
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
        //XLogi("av_read_frame  failed!");
        //读取失败，释放内存
        av_packet_free(&pkt);
        return {};
    }
    //XLogi("packet size is %d ,pts is %lld", pkt->size, pkt->pts);
    d.data = reinterpret_cast<unsigned char *>(pkt);
    d.size = pkt->size;

    if (pkt->stream_index == audioStreamIndex) {
        //如果是音频数据
        d.isAudio = true;
    } else if (pkt->stream_index == videoSteamIndex) {
        //如果是视频数据
        d.isAudio = false;
    } else {
        //如果两者都不是，销毁数据
        av_packet_free(&pkt);
        return {};
    }
    return d;
}

//获取视频参数
XParameter FFDemux::GetVideoParams() {
    if (!ic) {
        XLogi("GetVideoParams failed ic is NULL");
        return {};
    }
    //获取视频流索引
    int videoIndex = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    if (videoIndex < 0) {
        XLogi("av_find_best_stream failed");
        return {};
    }
    videoSteamIndex = videoIndex;
    XParameter parameter;
    parameter.parameters = ic->streams[videoIndex]->codecpar;
    return parameter;
}

//获取音频参数
XParameter FFDemux::GetAudioParams() {
    if (!ic) {
        XLogi("GetAudioParams failed ic is NULL");
        return {};
    }

    //获取音频流索引
    int audioIndex = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
    if (audioIndex < 0) {
        XLogi("av_find_best_stream failed");
        return {};
    }
    audioStreamIndex = audioIndex;
    XParameter parameter;
    parameter.parameters = ic->streams[audioIndex]->codecpar;
    parameter.channels = ic->streams[audioIndex]->codecpar->channels;
    parameter.sample_rate = ic->streams[audioIndex]->codecpar->sample_rate;
    return parameter;
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