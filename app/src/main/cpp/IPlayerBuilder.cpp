//
// Created by 胡章孝 on 2019/5/17.
//

#include "IPlayerBuilder.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IResample.h"
#include "IVideoView.h"
#include "IAudioPlay.h"

IPlayer *IPlayerBuilder::BuilderPlayer(unsigned char index) {

    IPlayer *play = CreatePlayer(index);
    IDemux *de = CreateDemux();
    //打开视频解码器
    IDecode *vDecode = CreateDecode();
    //打开音频解码器
    IDecode *aDecode = CreateDecode();
    //添加观察者
    de->AddObs(vDecode);
    de->AddObs(aDecode);

    //显示观察视频解码器
    IVideoView *videoView = CreateVideoView();
    vDecode->AddObs(videoView);

    //重采样观察音频解码器
    IResample *resample = CreateResample();
    aDecode->AddObs(resample);

    //音频播放观察重采样
    IAudioPlay *audioPlay = CreateAudioPlayer();
    resample->AddObs(audioPlay);

    play->demux = de;
    play->audioDecode = aDecode;
    play->videoDecode = vDecode;
    play->resample = resample;
    play->audioPlay = audioPlay;
    play->videoView = videoView;

    return play;

}
