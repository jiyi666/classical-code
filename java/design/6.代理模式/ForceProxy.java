package com.example.javatestlib1;

interface IGamePlayer {
    /* 登录游戏 */
    public void login(String user,String password);
    /* 杀怪， 网络游戏的主要特色 */
    public void killBoss();
    /* 升级 */
    public void upgrade();
    /* 每个人都可以找一下自己的代理 */
    public IGamePlayer getProxy();
}

class GamePlayer implements IGamePlayer {
    private String name = "";
    private IGamePlayer proxy = null;

    public GamePlayer(String name){
        this.name = name;
    }
    /* 找到自己的代理 */
    public IGamePlayer getProxy(){
        this.proxy = new GamePlayerProxy(this);
        return this.proxy;
    }

    public void killBoss() {
        if(this.isProxy()){
            System.out.println(this.name + "在打怪！ ");
        }else{
            System.out.println("请使用指定的代理访问");
        }
    }

    public void login(String user, String password) {
        if(this.isProxy()){
            System.out.println("登录名为"+user+"的用户"+this.name+"登录成功！");
        }else{
            System.out.println("请使用指定的代理访问");;
        }
    }

    public void upgrade() {
        if(this.isProxy()){
            System.out.println(this.name + " 又升了一级！ ");
        }else{
            System.out.println("请使用指定的代理访问");
        }
    }
    /* 校验是否是代理访问 */
    private boolean isProxy(){
        if(this.proxy == null){
            return false;
        }else{
            return true;
        }
    }
}

class GamePlayerProxy implements IGamePlayer {
    private IGamePlayer gamePlayer = null;
    /* 构造函数传递用户名:指定给谁代理 */
    public GamePlayerProxy(IGamePlayer gamePlayer){
        this.gamePlayer = gamePlayer;
    }

    public void killBoss() {
        this.gamePlayer.killBoss();
    }

    public void login(String user, String password) {
        this.gamePlayer.login(user, password);
    }

    public void upgrade() {
        this.gamePlayer.upgrade();
    }
    /* 代理的代理暂时还没有， 就是自己 */
    public IGamePlayer getProxy(){
        return this;
    }
}




public class ForceProxy {
    public static void main(String[] args) {

        IGamePlayer player = new GamePlayer("张三");
        /* 定义一个代练者 */
        IGamePlayer proxy = player.getProxy();

        System.out.println("开始时间是： 2009-8-25 10:45");
        proxy.login("zhangSan", "password");

        proxy.killBoss();

        proxy.upgrade();

        System.out.println("结束时间是： 2009-8-26 03:40");
    }
}

