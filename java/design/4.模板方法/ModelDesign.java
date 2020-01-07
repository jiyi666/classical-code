package com.example.javatestlib;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/* 模板为抽象类 */
abstract class HummerModel {
    /*
     * 首先，这个模型要能够被发动起来，别管是手摇发动，还是电力发动，反正
     * 是要能够发动起来，那这个实现要在实现类里了,需要子类实现的方法全部为protected
     */
    protected abstract void start();

    protected abstract void stop();

    protected abstract void alarm();

    protected abstract void engineBoom();

    /* 公共方法为final */
    final public void run() {
        this.start();

        this.engineBoom();

        if(this.isAlarm()){
            this.alarm();
        }

        this.stop();
    }
    /* 钩子方法，默认喇叭是会响的 */
    protected  boolean isAlarm(){
        return true;
    }
}

/* 子类一:覆写父类中的抽象方法 */
class HummerH1Model extends HummerModel {
    private boolean alarmFlag = true;

    protected void alarm() {
        System.out.println("悍马H1鸣笛...");
    }

    protected void engineBoom() {
        System.out.println("悍马H1引擎声音是这样的...");
    }

    protected void start() {
        System.out.println("悍马H1发动...");
    }

    protected void stop() {
        System.out.println("悍马H1停车...");
    }

    protected boolean isAlarm() {
        return this.alarmFlag;
    }

    /* 要不要响喇叭，是由客户来决定的 */
    public void setAlarm(boolean isAlarm) {
        this.alarmFlag = isAlarm;
    }
}

/* 子类二:覆写父类中的抽象方法 */
class HummerH2Model extends HummerModel {
    protected void alarm() {
        System.out.println("悍马H2鸣笛...");
    }
    protected void engineBoom() {
        System.out.println("悍马H2引擎声音是这样的...");
    }
    protected void start() {
        System.out.println("悍马H2发动...");
    }
    protected void stop() {
        System.out.println("悍马H2停车...");
    }
    /* 默认没有喇叭的 */
    protected boolean isAlarm() {
        return false;
    }
}

public class ModelDesign {
    public static void main(String[] args) throws IOException {
        System.out.println("-------H1型号悍马--------");
        System.out.println("H1型号的悍马是否需要喇叭声响？0-不需要   1-需要");
        String type=(new BufferedReader(new InputStreamReader(System.in))).readLine();
        HummerH1Model h1 = new HummerH1Model();
        if(type.equals("0")){
            h1.setAlarm(false);
        }
        h1.run();
        System.out.println("\n-------H2型号悍马--------");
        HummerH2Model h2 = new HummerH2Model();
        h2.run();
    }
}
