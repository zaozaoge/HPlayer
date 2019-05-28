package com.zaozao.hplayer;

import android.app.Activity;
import android.os.Bundle;
import android.support.v4.widget.ContentLoadingProgressBar;
import android.util.Log;
import android.view.View;

public class PlayActivity extends Activity implements Runnable {


    private ContentLoadingProgressBar progressBar;
    private Thread thread;

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        progressBar = findViewById(R.id.contentLoading);
        progressBar.hide();
    }


    public native void open(String path);

    public native boolean isReady();

    public native double getPlayProgress();

    public void openResource(View view) {
        progressBar.show();
        if (thread != null && thread.isAlive()) {
            thread.interrupt();
            thread = null;
        }
        thread = new Thread(this);
        thread.start();
    }

    @Override
    public void run() {
        //open("/sdcard/tencent/QQfile_recv/v1080.mp4");
        open("rtmp://live.hkstv.hk.lxdns.com/live/hks2");

        while (true) {
            double progress = getPlayProgress();
            if (isReady()) {
                Log.e("PlayActivity", "开始出图像了:" + progress);
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        progressBar.hide();
                    }
                });
                return;
            }
            try {
                Thread.sleep(40);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
