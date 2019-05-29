//
// Created by 胡章孝 on 2019/4/21.
//

#include "XThread.h"
#include "XLog.h"
#include <thread>

using namespace std;


void XSleep(int ms) {
    chrono::milliseconds du(ms);
    this_thread::sleep_for(du);
}

//启动线程
bool XThread::Start() {
    isExit = false;
    isPause = false;
    thread th(&XThread::ThreadMain, this);//启动线程
    th.detach();//放弃对该线程的控制，防止对象清空时相关的资源造成该线程出错
    return true;
}


void XThread::ThreadMain() {
    isRunning = true;
    XLogi("线程函数进入")
    Main();
    XLogi("线程函数退出")
    isRunning = false;
}

//通过控制isExit安全停止线程，不一定成功
void XThread::Stop() {
    isExit = true;
    isPause = false;
    for (int i = 1; i <= 200; i++) {
        if (!isRunning) {
            XLogi("停止线程成功！")
            return;
        }
        XSleep(1);
    }
    XLogi("停止线程超时!")
}

void XThread::SetPause(bool isPause) {
    this->isPause = isPause;
    //等待100毫秒
    for (int i = 0; i < 10; i++) {
        if (isPausing == isPause) {
            break;
        }
        XSleep(10);
    }
}
