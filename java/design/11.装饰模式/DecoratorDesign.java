package com.example.javatestlib;

/** 抽象成绩单 */
abstract class SchoolReport {
    //成绩单主要展示的就是你的成绩情况
    public abstract void report();
    //成绩单要家长签字， 这个是最要命的
    public abstract void sign(String name);
}

/** 具体实现类：四年级成绩单 */
class FouthGradeSchoolReport extends SchoolReport {
    //我的成绩单
    public void report() {
    //成绩单的格式是这个样子的
        System.out.println("尊敬的XXX家长:");
        System.out.println(" ......");System.out.println(" 语文 62 数学65 体育 98 自然 63");
        System.out.println(" .......");
        System.out.println(" 家长签名： ");
    }
    //家长签名
    public void sign(String name) {
        System.out.println("家长签名为： "+name);
    }
}

/** 装饰的抽象类 */
abstract class Decorator extends SchoolReport{
    //首先我要知道是哪个成绩单
    private SchoolReport sr;
    //构造函数， 传递成绩单过来
    public Decorator(SchoolReport sr){
        this.sr = sr;
    }
    //成绩单还是要被看到的
    public void report(){
        this.sr.report();
    }
    //看完还是要签名的
    public void sign(String name){
        this.sr.sign(name);
    }
}

/** 装饰最高成绩 */
class HighScoreDecorator extends Decorator {
    //构造函数
    public HighScoreDecorator(SchoolReport sr){
        super(sr);
    }
    //我要汇报最高成绩
    private void reportHighScore(){
        System.out.println("这次考试语文最高是75， 数学是78， 自然是80");
    }
    //我要在老爸看成绩单前告诉他最高成绩， 否则等他一看， 就抡起扫帚揍我， 我哪里还有机会说啊
    @Override
    public void report(){
        this.reportHighScore();
        super.report();
    }
}

/** 装饰排名 */
class SortDecorator extends Decorator {
    //构造函数
    public SortDecorator(SchoolReport sr){
        super(sr);
    }
    //告诉老爸学校的排名情况
    private void reportSort(){
        System.out.println("我是排名第38名...");
    }
    //老爸看完成绩单后再告诉他， 加强作用
    @Override
    public void report(){
        super.report();
        this.reportSort();
    }
}

public class DecoratorDesign {
    public static void main(String[] args) {
        //把成绩单拿过来
        SchoolReport sr;
        //原装的成绩单
        sr = new FouthGradeSchoolReport();
        //加了最高分说明的成绩单
        sr = new HighScoreDecorator(sr);
        //又加了成绩排名的说明
        sr = new SortDecorator(sr);
        //看成绩单
        sr.report();
        //然后老爸一看， 很开心， 就签名了
        sr.sign("老三"); //我叫小三， 老爸当然叫老三
    }
}
