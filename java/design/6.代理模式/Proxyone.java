package com.example.javatestlib;

interface IGamePlayer {
    /* 登录游戏 */
    public void login(String user,String password);
    /* 杀怪， 网络游戏的主要特色 */
    public void killBoss();
    /* 升级 */
    public void upgrade();
}

class GamePlayer implements IGamePlayer {
    private String name = "";

    public GamePlayer(IGamePlayer gamePlayer, String name) throws Exception{
        if (gamePlayer == null){
            throw new Exception("不能创建真实角色");
        } else {
            this.name = name;
        }
    }

    public void killBoss() {
        System.out.println(this.name + "在打怪！");
    }

    public void login(String user, String password) {
        System.out.println("登录名为"+user+"的用户"+this.name+"登录成功！");
    }

    public void upgrade() {
        System.out.println(this.name + " 又升了一级！ ");
    }
}

class GamePlayerProxy implements IGamePlayer {
    private IGamePlayer gamePlayer = null;

    public GamePlayerProxy(String name){
        try {
            gamePlayer = new GamePlayer(this, name);
        } catch (Exception e) {

        }
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
}

public class Proxyone {
    public static void main(String[] args) {

        IGamePlayer proxy = new GamePlayerProxy("张三");

        System.out.println("开始时间是： 2009-8-25 10:45");
        proxy.login("zhangSan", "password");

        proxy.killBoss();

        proxy.upgrade();

        System.out.println("结束时间是： 2009-8-26 03:40");
    }
}
