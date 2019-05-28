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

//分数转换为浮点数
static double r2d(AVRational r) {
    return r.num == 0 || r.den == 0 ? 0. : (double) r.num / (double) r.den;
}

//打开文件或者流媒体 rtmp http rtsp
bool FFDemux::Open(const char *url) {
    XLogi("open file %s begin", url);
    Close();
    mutex.lock();
    int result = avformat_open_input(&ic, url, nullptr, nullptr);
    if (result != 0) {
        char buf[1024] = {0};
        av_strerror(result, buf, sizeof(buf));
        XLogi("FFDemux open %s failed!", url);
        mutex.unlock();
        return false;
    }
    XLogi("FFDemux open %s success!", url);
    //读取文件信息
    result = avformat_find_stream_info(ic, nullptr);
    if (result != 0) {
        char buf[1024] = {0};
        av_strerror(result, buf, sizeof(buf));
        XLogi("avformat_find_stream_info %s failed!", url);
        mutex.unlock();
        return false;
    }
    this->totalMs = static_cast<int>(ic->duration / (AV_TIME_BASE / 1000));
    XLogi("total ms = %d", totalMs);
    mutex.unlock();
    GetVideoParams();
    GetAudioParams();
    return true;
}

//读取一帧数据，数据由调用者清理
XData FFDemux::Read() {
    mutex.lock();
    if (!ic) {
        mutex.unlock();
        return {};
    }
    XData d;
    AVPacket *pkt = av_packet_alloc();
    int result = av_read_frame(ic, pkt);
    if (result != 0) {
        mutex.unlock();
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
        mutex.unlock();
        av_packet_free(&pkt);
        return {};
    }

    //转换pts
    pkt->pts = (int) (pkt->pts * (1000 * r2d(ic->streams[pkt->stream_index]->time_base)));
    pkt->dts = (int) (pkt->dts * (1000 * r2d(ic->streams[pkt->stream_index]->time_base)));
    d.pts = (int) pkt->pts;

    mutex.unlock();
    return d;
}

//获取视频参数
XParameter FFDemux::GetVideoParams() {
    mutex.lock();
    if (!ic) {
        XLogi("GetVideoParams failed ic is NULL");
        mutex.unlock();
        return {};
    }
    //获取视频流索引
    int videoIndex = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    if (videoIndex < 0) {
        XLogi("av_find_best_stream failed");
        mutex.unlock();
        return {};
    }
    videoSteamIndex = videoIndex;
    XParameter parameter;
    parameter.parameters = ic->streams[videoIndex]->codecpar;
    mutex.unlock();
    return parameter;
}

//获取音频参数
XParameter FFDemux::GetAudioParams() {
    mutex.lock();
    if (!ic) {
        XLoge("GetAudioParams failed ic is NULL");
        mutex.unlock();
        return {};
    }

    //获取音频流索引
    int audioIndex = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
    if (audioIndex < 0) {
        XLogi("av_find_best_stream failed");
        mutex.unlock();
        return {};
    }
    audioStreamIndex = audioIndex;
    XParameter parameter;
    parameter.parameters = ic->streams[audioIndex]->codecpar;
    parameter.channels = ic->streams[audioIndex]->codecpar->channels;
    parameter.sample_rate = ic->streams[audioIndex]->codecpar->sample_rate;
    mutex.unlock();
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

void FFDemux::Close() {
    mutex.lock();
    if (ic) {
        avformat_close_input(&ic);
    }
    mutex.unlock();
}

bool FFDemux::Seek(double pos) {
    if (pos < 0 || pos > 1) {
        XLoge("pos must 0.0-1.0");
        return false;
    }
    bool result;
    mutex.lock();
    if (!ic) {
        mutex.unlock();
        return false;
    }
    //清空读写的数据
    avformat_flush(ic);
    long long seekPts = 0;
    seekPts = ic->streams[videoSteamIndex]->duration * pos;
    //往后跳转到关键帧
    result = av_seek_frame(ic, videoSteamIndex, seekPts, AVSEEK_FLAG_FRAME | AVSEEK_FLAG_BACKWARD);
    mutex.unlock();
    return result;
}
