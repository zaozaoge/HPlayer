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
            d = frames.front();
            frames.pop_front();
            framesMutex.unlock();
            return d;
        }
        framesMutex.unlock();
        XSleep(1);
    }
    return d;
}

