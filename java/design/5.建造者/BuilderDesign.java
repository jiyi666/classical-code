package com.example.javatestlib;

import java.util.ArrayList;

/* 产品抽象类 */
abstract class CarModel {
    /* 这个参数是各个基本方法执行的顺序 */
    private ArrayList<String> sequence = new ArrayList<String>();

    protected abstract void start();

    protected abstract void stop();

    protected abstract void alarm();

    protected abstract void engineBoom();

    final public void run() {
        for(int i = 0; i < this.sequence.size(); i++){
            String actionName = this.sequence.get(i);
            if(actionName.equalsIgnoreCase("start")){
                this.start();
            }else if(actionName.equalsIgnoreCase("stop")){
                this.stop();
            }else if(actionName.equalsIgnoreCase("alarm")){
                this.alarm();
            }else if(actionName.equalsIgnoreCase("engine boom")){
                this.engineBoom();
            }
        }
    }
    final public void setSequence(ArrayList sequence){
        this.sequence = sequence;
    }
}

/* 具体产品一：奔驰车 */
class BenzModel extends CarModel {
    protected void alarm() {
        System.out.println("奔驰车的喇叭声音是这个样子的...");
    }
    protected void engineBoom() {
        System.out.println("奔驰车的引擎是这个声音的...");
    }
    protected void start() {
        System.out.println("奔驰车跑起来是这个样子的...");
    }
    protected void stop() {
        System.out.println("奔驰车应该这样停车...");
    }
}

/* 具体产品一：宝马车 */
class BMWModel extends CarModel {
    protected void alarm() {
        System.out.println("宝马车的喇叭声音是这个样子的...");
    }
    protected void engineBoom() {
        System.out.println("宝马车的引擎是这个声音的...");
    }
    protected void start() {
        System.out.println("宝马车跑起来是这个样子的...");
    }
    protected void stop() {
        System.out.println("宝马车应该这样停车...");
    }
}

/* 建造者抽象类 */
abstract class CarBuilder {
    /* 建造一个模型， 你要给我一个顺序要求， 就是组装顺序 */
    public abstract void setSequence(ArrayList<String> sequence);
    /* 设置完毕顺序后， 就可以直接拿到这个车辆模型 */
    public abstract CarModel getCarModel();
}

/* 建造者具体类：奔驰车 */
class BenzBuilder extends CarBuilder {
    private BenzModel benz = new BenzModel();
    public CarModel getCarModel() {
        return this.benz;
    }
    public void setSequence(ArrayList<String> sequence) {
        this.benz.setSequence(sequence);
    }
}

/* 建造者具体类：宝马车 */
class BMWBuilder extends CarBuilder {
    private BMWModel bmw = new BMWModel();
    public CarModel getCarModel() {
        return this.bmw;
    }
    public void setSequence(ArrayList<String> sequence) {
        this.bmw.setSequence(sequence);
    }
}

/* 导演类用于封装 */
class Director {
    private ArrayList<String> sequence = new ArrayList();
    private BenzBuilder benzBuilder = new BenzBuilder();
    private BMWBuilder bmwBuilder = new BMWBuilder();
    /**
     * A类型的奔驰车模型， 先start， 然后stop， 其他什么引擎、 喇叭一概没有
     */
    public BenzModel getABenzModel(){
        this.sequence.clear();
        this.sequence.add("start");
        this.sequence.add("stop");
        this.benzBuilder.setSequence(this.sequence);
        return (BenzModel)this.benzBuilder.getCarModel();
    }
    /**
    B型号的奔驰车模型， 是先发动引擎， 然后启动， 然后停止， 没有喇叭
    */
    public BenzModel getBBenzModel(){
        this.sequence.clear();
        this.sequence.add("engine boom");
        this.sequence.add("start");
        this.sequence.add("stop");this.benzBuilder.setSequence(this.sequence);
        return (BenzModel)this.benzBuilder.getCarModel();
    }
    /**
    C型号的宝马车是先按下喇叭（炫耀嘛） ， 然后启动， 然后停止
    */
    public BMWModel getCBMWModel(){
        this.sequence.clear();
        this.sequence.add("alarm");
        this.sequence.add("start");
        this.sequence.add("stop");
        this.bmwBuilder.setSequence(this.sequence);
        return (BMWModel)this.bmwBuilder.getCarModel();
    }
    /**
    D类型的宝马车只有一个功能， 就是跑， 启动起来就跑， 永远不停止
    */
    public BMWModel getDBMWModel(){
        this.sequence.clear();
        this.sequence.add("start");
        this.bmwBuilder.setSequence(this.sequence);
        return (BMWModel)this.benzBuilder.getCarModel();
    }
}

public class BuilderDesign {
    public static void main(String[] args) {
        /* 直接创建导演类来控制建造者 */
        Director director = new Director();
        for(int i = 0; i < 2; i++){
            director.getABenzModel().run();
        }
        for(int i = 0; i < 3; i++){
            director.getBBenzModel().run();
        }
        for(int i = 0; i < 2; i++){
            director.getCBMWModel().run();
        }
    }
}
