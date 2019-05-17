//
// Created by 胡章孝 on 2019/5/17.
//

#include "FFPlayerBuilder.h"
#include "FFDemux.h"
#include "FFDecode.h"
#include "FFResample.h"
#include "GLVideoView.h"
#include "SLAudioPlay.h"

IDemux *FFPlayerBuilder::CreateDemux() {
    IDemux *demux = new FFDemux();
    return demux;
}

IDecode *FFPlayerBuilder::CreateDecode() {
    IDecode *decode = new FFDecode();
    return decode;
}

IResample *FFPlayerBuilder::CreateResample() {
    IResample *resample = new FFResample();
    return resample;
}


IVideoView *FFPlayerBuilder::CreateVideoView() {
    IVideoView *videoView = new GLVideoView();
    return videoView;
}

IAudioPlay *FFPlayerBuilder::CreateAudioPlayer() {
    IAudioPlay *audioPlay = new SLAudioPlay();
    return audioPlay;
}

IPlayer *FFPlayerBuilder::CreatePlayer(unsigned char index) {
    return IPlayer::Get(index);
}

void FFPlayerBuilder::InitHard(void *vm) {
    FFDecode::InitHard(vm);
}