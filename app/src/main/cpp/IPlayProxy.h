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

    virtual bool Open(const char *path);

    bool Start() override;

    virtual void InitView(void *win);


protected:

    IPlayProxy() = default;

    IPlayer *player = nullptr;
    std::mutex mutex;
};


#endif //ZPLAYER_IPLAYPROXY_H
