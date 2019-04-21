//
// Created by 胡章孝 on 2019/4/13.
//




class XLog {

};

#ifdef ANDROID

#include <android/log.h>

#define XLogd(...) __android_log_print(ANDROID_LOG_DEBUG,"ZPlay",__VA_ARGS__);
#define XLogi(...) __android_log_print(ANDROID_LOG_INFO,"ZPlay",__VA_ARGS__);
#define XLoge(...) __android_log_print(ANDROID_LOG_ERROR,"ZPlay",__VA_ARGS__);
#else
#define XLogd(...) printf(ANDROID_LOG_DEBUG,"ZPlay",__VA_ARGS__);
#define XLogi(...) printf(ANDROID_LOG_INFO,"ZPlay",__VA_ARGS__);
#define XLoge(...) printf(ANDROID_LOG_ERROR,"ZPlay",__VA_ARGS__);
#endif ZPLAYER_XLOG_H
