//
// Created by 胡章孝 on 2019/5/14.
//

#include "IAudioPlay.h"
#include "XLog.h"

void IAudioPlay::Update(XData xData) {

    //压入缓冲队列
    if (!xData.data || xData.size <= 0) {
        return;
    }
    while (!isExit) {
        framesMutex.lock();
        if (frames.size() > maxFrames) {
            framesMutex.unlock();
            XSleep(1);
            continue;
        }
        frames.push_back(xData);
        framesMutex.unlock();
        break;
    }

}

XData IAudioPlay::GetData() {
    XData d;
    while (!isExit) {
        framesMutex.lock();
        if (!frames.empty()) {
            //有数据返回
            d = frames.front();
            frames.pop_front();
            framesMutex.unlock();
            pts = d.pts;
            return d;
        }
        framesMutex.unlock();
        XSleep(1);
    }
    //未获取数据
    return d;
}

void IAudioPlay::Clear() {
    framesMutex.lock();
    while (!frames.empty()) {
        frames.front().Drop();
        frames.pop_front();
    }
    framesMutex.unlock();
}

