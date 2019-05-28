//
// Created by 胡章孝 on 2019/5/18.
//

#ifndef ZPLAYER_IPLAYPROXY_H
#define ZPLAYER_IPLAYPROXY_H


#include <mutex>
#include "IPlayer.h"

class IPlayProxy : public IPlayer {
public:

    static IPlayProxy *Get() {
        static IPlayProxy playProxy;
        return &playProxy;
    }

    void Init(void *vm = 0);

    bool Open(const char *path) override;

    double PlayPos() override;

    bool IsReady() override;

    void Close() override;

    bool Start() override;

    bool Seek(double pos) override;

    void SetPause(bool isPause) override;

    bool IsPause() override;

    void InitView(void *win) override;


protected:

    IPlayProxy() = default;

    IPlayer *player = nullptr;
    std::mutex mutex;
};


#endif //ZPLAYER_IPLAYPROXY_H
