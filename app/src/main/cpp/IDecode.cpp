//
// Created by 胡章孝 on 2019/4/21.
//

#include "IDecode.h"
#include "XLog.h"


void IDecode::Update(XData pkt) {
    if (pkt.isAudio != isAudio) {
        return;
    }

    while (!isExit) {
        packetMutex.lock();
        if (packs.size() < maxList) {
            //堵塞,生产者
            packs.push_back(pkt);
            packetMutex.unlock();
            break;
        }
        packetMutex.unlock();
        XSleep(1);
    }


}

void IDecode::Main() {
    while (!isExit) {
        if (IsPause()) {
            XSleep(2);
            continue;
        }

        packetMutex.lock();

        //判断音视频同步

        if (!isAudio && synPTS > 0) {
            if (synPTS < pts) {
                //音频播放慢于视频播放速度，则挺下来等待音频
                packetMutex.unlock();
                XSleep(1);
                continue;
            }
        }
        if (packs.empty()) {
            packetMutex.unlock();
            XSleep(1);
            continue;
        }
        //取出packet，消费者
        XData packet = packs.front();
        //从链表中删除
        packs.pop_front();
        //发送数据到解码线程，一个数据包可能包含多个解码结果
        if (this->SendPacket(packet)) {
            while (!isExit) {
                //获取解码数据
                XData frame = ReceiveFrame();
                if (!frame.data)break;
                //XLoge("ReceiveFrame size is %d", frame.size);
                pts = frame.pts;
                //发送数据给观察者
                this->Notify(frame);

            }
        }
        packet.Drop();
        packetMutex.unlock();
    }

}

void IDecode::Clear() {

    packetMutex.lock();
    while (!packs.empty()) {
        packs.front().Drop();
        packs.pop_front();
    }
    pts = 0;
    synPTS = 0;
    packetMutex.unlock();
}

