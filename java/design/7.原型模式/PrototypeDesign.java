package com.example.javatestlib;

import java.util.Random;

/** 广告信模板 */
class AdvTemplate {

    private String advSubject ="XX银行国庆信用卡抽奖活动";

    private String advContext = "国庆抽奖活动通知： 只要刷卡就送你一百万！ ...";

    public String getAdvSubject(){
        return this.advSubject;
    }

    public String getAdvContext(){
        return this.advContext;
    }
}

/** 邮件实现类：邮件定制化内容 + 通用内容（广告） */
class Mail implements Cloneable{

    private String receiver;

    private String subject;

    private String appellation;

    private String contxt;

    private String tail;

    public Mail (AdvTemplate advTemplate){
        this.contxt = advTemplate.getAdvContext();
        this.subject = advTemplate.getAdvSubject();
    }

    public String getReceiver() {
        return receiver;
    }
    public void setReceiver(String receiver) {
        this.receiver = receiver;
    }
    public String getSubject() {
        return subject;
    }
    public void setSubject(String subject) {
        this.subject = subject;
    }
    public String getAppellation() {
        return appellation;
    }
    public void setAppellation(String appellation) {
        this.appellation = appellation;
    }
    public String getContxt() {
        return contxt;
    }
    public void setContxt(String contxt) {
        this.contxt = contxt;
    }
    public String getTail() {
        return tail;
    }
    public void setTail(String tail) {
        this.tail = tail;
    }
    @Override
    public Mail clone(){
        Mail mail = null;
        try{
            mail = (Mail)super.clone();
        } catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }
        return mail;
    }
}

public class PrototypeDesign {

    private static int MAX_COUNT = 6;

    public static void main(String[] args) {

        int i=0;

        Mail mail = new Mail(new AdvTemplate());
        mail.setTail("XX银行版权所有");
        while(i<MAX_COUNT){
            /* 每封邮件的不同 */
            Mail cloneMainl = mail.clone(); //调用Mail的clone方法
            mail.setAppellation(getRandString(5)+" 先生（女士） ");
            mail.setReceiver(getRandString(5)+"@"+getRandString(8));
            sendMail(cloneMainl);
            i++;
        }
    }
    /* 邮件发送函数 */
    public static void sendMail(Mail mail){
        System.out.println("标题： "+mail.getSubject() + "\t收件人：" +
                mail.getReceiver() + "\t...发送成功！ ");
    }
    /* 获得指定长度的随机字符串 */
    public static String getRandString(int maxLength){
        String source ="abcdefghijklmnopqrskuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        StringBuffer sb = new StringBuffer();
        Random rand = new Random();
        for(int i = 0; i < maxLength; i++){
            sb.append(source.charAt(rand.nextInt(source.length())));
        }
        return sb.toString();
    }
}
