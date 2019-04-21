//
// Created by 胡章孝 on 2019/4/13.
//

#include "XData.h"

extern "C" {
#include "include/libavcodec/avcodec.h"

}

void XData::Drop() {
    if (!data) {
        av_packet_free(reinterpret_cast<AVPacket **>(&data));
        data = 0;
        size = 0;
    }
}
