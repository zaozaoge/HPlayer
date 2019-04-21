//
// Created by 胡章孝 on 2019/4/21.
//

#include "XThread.h"
#include "XLog.h"
#include <thread>

using namespace std;

//启动线程
void XThread::Start() {
    thread th(&XThread::ThreadMain, this);//启动线程
    th.detach();//放弃对该线程的控制，防止对象清空时相关的资源造成该线程出错
}


void XThread::ThreadMain() {
    XLogi("线程函数进入")
    Main();
    XLogi("线程函数退出")
}

//通过控制isExit安全停止线程，不一定成功
void XThread::Stop() {

}
