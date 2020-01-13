package com.example.javatestlib;


import java.util.ArrayList;
import java.util.Random;

interface IWomen {
    //获得个人状况
    public int getType();
    //获得个人请示， 你要干什么？ 出去逛街？ 约会?还是看电影？
    public String getRequest();
}

/**
 * 通过一个int类型的参数来描述妇女的个人状况
 * 1--未出嫁
 * 2--出嫁
 * 3--夫死
 */
class Women implements IWomen{
    private int type=0;
    //妇女的请示
    private String request = "";
    //构造函数传递过来请求
    public Women(int type,String request){
        this.type = type;

        switch(this.type){
            case 1:
                this.request = "女儿的请求是： " + request;
                break;
            case 2:
                this.request = "妻子的请求是： " + request;
                break;
            case 3:
                this.request = "母亲的请求是： " + request;
        }
    }
    //获得自己的状况
    public int getType(){
        return this.type;
    }
    //获得妇女的请求
    public String getRequest(){
        return this.request;
    }
}

/** 处理权人员接口 */
abstract class Handler {
    public final static int FATHER_LEVEL_REQUEST = 1;
    public final static int HUSBAND_LEVEL_REQUEST = 2;
    public final static int SON_LEVEL_REQUEST = 3;
    //能处理的级别
    private int level = 0;
    //责任传递， 下一个人责任人是谁
    private Handler nextHandler;
    //每个类都要说明一下自己能处理哪些请求
    public Handler(int level){
        this.level = level;
    }

    public final void HandleMessage(IWomen women){
        if(women.getType() == this.level){
            this.response(women);
        }else{
            if(this.nextHandler != null){
            }else{
                System.out.println("---没地方请示了， 按不同意处理---\n");
            }
        }
    }
    /**
    如果不属于你处理的请求， 你应该让她找下一个环节的人， 如女儿出嫁了，
            * 还向父亲请示是否可以逛街， 那父亲就应该告诉女儿， 应该找丈夫请示
    */
    public void setNext(Handler handler){
        this.nextHandler = handler;
    }
    protected abstract void response(IWomen women);
}


/** 父亲类 */
class Father extends Handler {
    //父亲只处理女儿的请求
    public Father(){
        super(Handler.FATHER_LEVEL_REQUEST);
    }
    //父亲的答复
    protected void response(IWomen women) {
        System.out.println("--------女儿向父亲请示-------");
        System.out.println(women.getRequest());
        System.out.println("父亲的答复是:同意\n");
    }
}
/** 丈夫类 */
class Husband extends Handler {
    //丈夫只处理妻子的请求
    public Husband(){super(Handler.HUSBAND_LEVEL_REQUEST);
    }
    //丈夫请示的答复
    protected void response(IWomen women) {
        System.out.println("--------妻子向丈夫请示-------");
        System.out.println(women.getRequest());
        System.out.println("丈夫的答复是： 同意\n");
    }
}

/** 儿子类 */
class Son extends Handler {
    //儿子只处理母亲的请求
    public Son(){
        super(Handler.SON_LEVEL_REQUEST);
    }
    //儿子的答复
    protected void response(IWomen women) {
        System.out.println("--------母亲向儿子请示-------");
        System.out.println(women.getRequest());
        System.out.println("儿子的答复是： 同意\n");
    }
}

public class ResponsibilityDesign {
    public static void main(String[] args) {
        //随机挑选几个女性
        Random rand = new Random();
        ArrayList<IWomen> arrayList = new ArrayList();
        for(int i=0;i<5;i++){
            arrayList.add(new Women(rand.nextInt(4),"我要出去逛街"));
        }
        //定义三个请示对象
        Handler father = new Father();
        Handler husband = new Husband();
        Handler son = new Son();
        //设置请示顺序
        father.setNext(husband);
        husband.setNext(son);
        for(IWomen women:arrayList){
            father.HandleMessage(women);
        }
    }
}
