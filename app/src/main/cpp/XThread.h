//
// Created by 胡章孝 on 2019/4/21.
//

#ifndef ZPLAYER_XTHREAD_H
#define ZPLAYER_XTHREAD_H

//Sleep 毫秒
void XSleep(int ms);
//c++ 11线程库
class XThread {
public:
    //启动线程
    virtual void Start();

    //通过控制isExit安全停止线程，不一定成功
    virtual void Stop();

    //入口主函数
    virtual void Main() {

    }

protected:
    bool isExit = false;
    bool isRunning = false;
private:
    void ThreadMain();
};


#endif //ZPLAYER_XTHREAD_H
