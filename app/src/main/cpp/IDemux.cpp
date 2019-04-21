//
// Created by 胡章孝 on 2019/4/13.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::Main() {
    bool isExit = false;
    while (!isExit) {
        XData data = Read();
        XLogi("Idemux Read %d", data.size);
        if (data.size <= 0) {
            isExit = true;
        }

    }
}