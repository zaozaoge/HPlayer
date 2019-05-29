package com.zaozao.hplayer;

import android.app.Activity;
import android.os.Bundle;
import android.support.v4.widget.ContentLoadingProgressBar;
import android.support.v7.widget.AppCompatSeekBar;
import android.util.Log;
import android.view.View;
import android.widget.SeekBar;

public class PlayActivity extends Activity implements Runnable {


    private ContentLoadingProgressBar progressBar;
    private Thread thread;
    private AppCompatSeekBar seekBar;
    private boolean flag = true;
    private boolean isTracking = false;

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        progressBar = findViewById(R.id.contentLoading);
        seekBar = findViewById(R.id.seekBar);
        seekBar.setMax(100);
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                isTracking = true;
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                isTracking = false;
                Log.e("ZP", "onStopTrackingTouch:" + (double) seekBar.getProgress() / (double) seekBar.getMax());
                seek((double) seekBar.getProgress() / (double) seekBar.getMax());
            }
        });
        progressBar.hide();
    }


    public native void open(String path);

    public native boolean isReady();

    public native double getPlayProgress();

    public native void seek(double pos);

    public native void close();

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
        open("/sdcard/tencent/QQfile_recv/v1080.mp4");
        //open("rtmp://live.hkstv.hk.lxdns.com/live/hks2");

        while (flag) {
            double progress = getPlayProgress();
            if (!isTracking)
                seekBar.setProgress((int) (progress * 100));
            if (isReady()) {
                Log.e("PlayActivity", "开始出图像了:" + progress);
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        progressBar.hide();
                    }
                });
            }
            try {
                Thread.sleep(40);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        flag = false;
        close();
    }
}
