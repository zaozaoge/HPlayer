//
// Created by 胡章孝 on 2019/4/21.
//

#include "IObserver.h"

//主体函数，添加观察者
void IObserver::AddObs(IObserver *obs) {
    if (!obs)
        return;
    mux.lock();
    obss.push_back(obs);
    mux.unlock();
}

//通知所有观察者
void IObserver::Notify(XData data) {
    mux.lock();
    for (auto &obs : obss) {
        obs->Update(data);
    }
    mux.unlock();
}
