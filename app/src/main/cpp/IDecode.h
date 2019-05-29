//
// Created by 胡章孝 on 2019/4/21.
//

#ifndef ZPLAYER_IDEOCDE_H
#define ZPLAYER_IDEOCDE_H

#include "XParameter.h"
#include "IObserver.h"
#include <list>

//解码接口，支持硬解码
class IDecode : public IObserver {
public:

    static void InitHard(void *vm);


    //打开解码器
    virtual bool Open(XParameter xParameter, bool isHard = false) = 0;


    virtual void Close() = 0;
    virtual void Clear();
    //future模型,发送数据到线程解码
    virtual bool SendPacket(XData pkt) = 0;

    //从线程中获取解码结果
    virtual XData ReceiveFrame() = 0;

    //由主体notify的数据 堵塞
    void Update(XData pkt) override;

    //判断当前是否是音频
    bool isAudio = false;

    //最大的队列缓冲
    int maxList = 100;

    //同步时间，再次打开文件要清零
    int synPTS = 0;
    //当前播放到的位置
    int pts = 0;
protected:

    virtual void Main();

    //读取缓冲
    std::list<XData> packs;
    std::mutex packetMutex;
};


#endif //ZPLAYER_IDEOCDE_H
