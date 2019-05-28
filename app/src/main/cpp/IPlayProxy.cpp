//
// Created by 胡章孝 on 2019/5/18.
//

#include "IPlayProxy.h"
#include "FFPlayerBuilder.h"
#include "XLog.h"

bool IPlayProxy::Open(const char *path) {
    bool result = false;
    XLoge("打开文件：%s", path);
    mutex.lock();
    if (player) {
        player->isHardDecode = isHardDecode;
        result = player->Open(path);
    }
    XLoge("打开文件：%d", result);
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
    XLoge("开始执行");
    mutex.lock();
    XLoge("开启线程");
    if (player) {
        result = player->Start();
    }
    XLoge("开启线程结束");
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

void IPlayProxy::Close() {
    mutex.lock();
    if (player) {
        player->Close();
    }
    mutex.unlock();
}

double IPlayProxy::PlayPos() {

    mutex.lock();
    double pos = 0.0;
    if (player) {
        pos = player->PlayPos();
    }
    mutex.unlock();
    return pos;
}

bool IPlayProxy::IsReady() {
    mutex.lock();
    if (player) {
        mutex.unlock();
        return player->IsReady();
    }
    mutex.unlock();
    return false;
}

bool IPlayProxy::Seek(double pos) {
    bool result = false;
    mutex.lock();
    if (player) {
        result = player->Seek(pos);
    }
    mutex.unlock();
    return result;
}

void IPlayProxy::SetPause(bool isPause) {
    mutex.lock();
    if (player) {
        player->SetPause(isPause);
    }
    mutex.unlock();
}

bool IPlayProxy::IsPause() {
    bool result = false;
    mutex.lock();
    if (player) {
        result = player->IsPause();
    }
    mutex.unlock();
    return result;
}
