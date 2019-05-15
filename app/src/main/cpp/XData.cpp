//
// Created by 胡章孝 on 2019/4/13.
//

#include "XData.h"

extern "C" {
#include "include/libavcodec/avcodec.h"

}

void XData::Drop() {

    if (!data)
        return;;
    if (type == AVPACKET_TYPE) {
        av_packet_free(reinterpret_cast<AVPacket **>(&data));
    } else {
        delete data;
    }
    data = 0;
    size = 0;
}

bool XData::Alloc(int size, const char *data) {
    Drop();
    type = UCHAR_TYPE;
    if (size <= 0)
        return false;
    this->data = new unsigned char[size];
    if (!this->data)
        return false;
    if (data) {
        memcpy(this->data, data, static_cast<size_t>(size));
    }
    this->size = size;
    return true;
}
