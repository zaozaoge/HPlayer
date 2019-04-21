//
// Created by 胡章孝 on 2019/4/13.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::Main() {
    while (!isExit) {
        XData data = Read();
        if (data.size > 0) {
            Notify(data);
        }
        // XLogi("Idemux Read %d", data.size);
    }
}