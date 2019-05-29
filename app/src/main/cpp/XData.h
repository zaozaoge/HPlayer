//
// Created by 胡章孝 on 2019/4/13.
//

#ifndef ZPLAYER_XDATA_H
#define ZPLAYER_XDATA_H

enum XDataType {
    AVPACKET_TYPE = 0,
    UCHAR_TYPE = 1
};

struct XData {
    int type = 0;
    int pts = 0;
    unsigned char *data = nullptr;
    unsigned char *datas[8] = {nullptr};
    int size = 0;
    bool isAudio = false;
    int width = 0;
    int height = 0;
    int format = 0;//数据格式

    bool Alloc(int size, const char *data = nullptr);

    void Drop();
};


#endif //ZPLAYER_XDATA_H
