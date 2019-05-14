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
        packetMutex.lock();
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
                //发送数据给观察者
                this->Notify(frame);

            }
        }
        packet.Drop();
        packetMutex.unlock();
    }

}

