//
// Created by 胡章孝 on 2019/5/11.
//

#include <android/native_window.h>
#include "XEGL.h"
#include "XLog.h"
#include <EGL/egl.h>
#include <mutex>

class CXEGL : public XEGL {

public:

    EGLDisplay display = EGL_NO_DISPLAY;
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;
    std::mutex mutex;

    virtual void Draw() {
        mutex.lock();
        if (display == EGL_NO_DISPLAY || surface == EGL_NO_SURFACE) {
            mutex.unlock();
            return;
        }
        eglSwapBuffers(display, surface);
        mutex.unlock();
    }

    virtual void Close() {
        mutex.lock();
        if (display == EGL_NO_DISPLAY) {
            mutex.unlock();
            return;
        }
        //去除绑定关系
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (surface != EGL_NO_SURFACE) {
            //销毁surface
            eglDestroySurface(display, surface);
        }
        if (context != EGL_NO_CONTEXT) {
            //销毁context
            eglDestroyContext(display, context);
        }
        //中止display
        eglTerminate(display);
        display = EGL_NO_DISPLAY;
        surface = EGL_NO_SURFACE;
        context = EGL_NO_CONTEXT;
        mutex.unlock();
    }

    virtual bool Init(void *win) {
        Close();
        auto window = static_cast<ANativeWindow *>(win);
        //初始化EGL
        mutex.lock();
        //1、获取EGLDisplay对象，显示设备
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY) {
            XLogi("eglGetDisplay failed");
            mutex.unlock();
            return false;
        }
        XLogi("eglGetDisplay success");
        //2、初始化Display
        if (EGL_TRUE != eglInitialize(display, 0, 0)) {
            XLogi("eglInitialize failed");
            mutex.unlock();
            return false;
        }
        XLogi("eglInitialize success");
        //3、配置并创建surface
        EGLint configSpec[] = {
                EGL_RED_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_BLUE_SIZE, 8,
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_NONE
        };
        EGLConfig config = 0;
        EGLint numConfigs = 0;
        if (EGL_TRUE != eglChooseConfig(display, configSpec, &config, 1, &numConfigs)) {
            XLogi("eglChooseConfig failed");
            mutex.unlock();
            return false;
        }
        XLogi("eglChooseConfig success");
        surface = eglCreateWindowSurface(display, config, window, nullptr);

        //4、创建并打开上下文
        const EGLint ctxAttr[]{
                EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
        };
        context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttr);
        if (context == EGL_NO_CONTEXT) {
            XLogi("eglCreateContext failed");
            mutex.unlock();
            return false;
        }
        XLogi("eglCreateContext success");
        if (EGL_TRUE != eglMakeCurrent(display, surface, surface, context)) {
            XLogi("eglMakeCurrent failed");
            mutex.unlock();
            return false;
        }
        XLogi("eglMakeCurrent success");
        mutex.unlock();
        return true;
    }
};

XEGL *XEGL::Get() {
    static CXEGL egl;
    return &egl;
}




