//
// Created by 胡章孝 on 2019/4/21.
//

#ifndef ZPLAYER_XPARAMETER_H
#define ZPLAYER_XPARAMETER_H


struct AVCodecParameters;

class XParameter {
public:
    AVCodecParameters *parameters = 0;
    int channels = 2;
    int sample_rate = 44100;
};


#endif //ZPLAYER_XPARAMETER_H
