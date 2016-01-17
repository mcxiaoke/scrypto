package com.mcxiaoke.ndk;

/**
 * Author: mcxiaoke
 * Date:  2016/1/17 13:14
 */
public final class Native {

    static {
        System.loadLibrary("native");
    }

    public native static String debugInfo();

}
