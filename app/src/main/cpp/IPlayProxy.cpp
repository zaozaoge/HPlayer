//
// Created by 胡章孝 on 2019/5/18.
//

#include "IPlayProxy.h"
#include "FFPlayerBuilder.h"

bool IPlayProxy::Open(const char *path) {
    bool result = false;
    mutex.lock();
    if (player) {
        result = player->Open(path);
    }
    mutex.unlock();
    return result;

}

void IPlayProxy::InitView(void *win) {
    mutex.lock();
    if (player) {
        player->InitView(win);
    }
    mutex.unlock();
}

bool IPlayProxy::Start() {
    bool result = false;
    mutex.lock();
    if (player) {
        result = player->Start();
    }
    mutex.unlock();
    return result;
}

void IPlayProxy::Init(void *vm) {
    mutex.lock();
    if (vm) {
        FFPlayerBuilder::InitHard(vm);
    }
    if (!player) {
        player = FFPlayerBuilder::Get()->BuilderPlayer();
    }
    mutex.unlock();
}
