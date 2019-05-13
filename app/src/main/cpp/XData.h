//
// Created by 胡章孝 on 2019/4/13.
//

#ifndef ZPLAYER_XDATA_H
#define ZPLAYER_XDATA_H


struct XData {
    unsigned char *data = 0;
    unsigned char *datas[8] = {0};
    int size = 0;
    bool isAudio = false;
    int width = 0;
    int height = 0;

    void Drop();
};


#endif //ZPLAYER_XDATA_H
