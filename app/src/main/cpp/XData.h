//
// Created by 胡章孝 on 2019/4/13.
//

#ifndef ZPLAYER_XDATA_H
#define ZPLAYER_XDATA_H


struct XData {
    unsigned char *data = 0;
    int size  = 0;
    void Drop();
};


#endif //ZPLAYER_XDATA_H
