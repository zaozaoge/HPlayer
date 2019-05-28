//
// Created by 胡章孝 on 2019/4/13.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::Main() {
    while (!isExit) {

        if (IsPause()) {
            XSleep(2);
            continue;
        }
        XData data = Read();
        if (data.size > 0) {
            Notify(data);
        } else {
            XSleep(2);
        }
        // XLogi("Idemux Read %d", data.size);
    }
}